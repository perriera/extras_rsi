/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * The above copyright notice and  this permission  notice shall be
 * included in all copies or  substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESSED  OR   IMPLIED,  INCLUDING   BUT  NOT  LIMITED  TO  THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT.  IN  NO  EVENT  SHALL EXPARX  INCORPORATED
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER  IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM, OUT  OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR  OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Except  as  contained  in this  notice, the  name of  the EXPARX
 * INCORPORATED shall not  be used in  advertising or  otherwise to
 * promote the sale, use or other dealings in this Software without
 * prior written authorization from EXPARX INCORPORATED.
 *
 * exparx.com and www.exparx.com  are domain names  registered with
 * EXPARX INCORPORATED, (other GPL-themed licenses are included).
 *
 */

#include <rsi/sockets/Semaphores.hpp>
#include <rsi/uploader/Uploader.hpp>
#include <rsi/parcel/Wrap.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/status/StatusLine.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/system.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace std;
using namespace fakeit;
namespace fs = std::filesystem;

static std::string client_dir = "data/client/";
static std::string server_dir = "data/server/";
static const std::string original = ~extras::Paths("data/exparx.webflow.zip");

static void clean() {
    rsi::Parcel parcel(original);
    parcel.clean();
    rsi::ParcelImploder parcelImploder;
    parcelImploder.clean(original);
    if (fs::exists(client_dir))
        fs::remove_all(client_dir);
    if (fs::exists(server_dir))
        fs::remove_all(server_dir);
}

static void prepare() {
    clean();
    SystemException::assertion("mkdir " + client_dir, __INFO__);
    SystemException::assertion("mkdir " + server_dir, __INFO__);
    auto cp_cmd = "cp " + original + " " + client_dir;
    SystemException::assertion(cp_cmd, __INFO__);
}

SCENARIO("Mock SemaphoreInterface: Uploader", "[SemaphoreInterface]") {

    /**
     * @brief Mock<rsi::UploaderInterface> uploader;
     *
     */
    rsi::BinFile internet;
    rsi::UploaderStatus status;

    Mock<rsi::UploaderInterface> semaphore;
    When(Method(semaphore, send))
        .AlwaysDo(
            [&internet](const rsi::Filename& filename) {
                ifstream in(filename);
                rsi::BinFile binFile = rsi::ConvertFile().loadBin(in);
                internet = binFile;
            });
    When(Method(semaphore, write))
        .AlwaysDo(
            [&internet](const rsi::Filename& filename) {
                if (!fs::exists(server_dir)) {
                    SystemException::assertion("mkdir " + server_dir, __INFO__);
                }
                if (internet.size() == 0)
                    throw "Nothing to save";
                auto target = extras::replace_all(filename, client_dir, server_dir);
                ofstream out(target);
                rsi::ConvertFile().saveBin(out, internet);
                internet.clear();
                return target;
            });
    When(Method(semaphore, send_line))
        .AlwaysDo(
            [&status](const rsi::UploaderStatus& msg) {
                status = msg;
            });
    When(Method(semaphore, read_line))
        .AlwaysDo(
            [&status]() {
                auto msg = status;
                status.clear();
                return msg;
            });

    // clean();
    rsi::UploaderInterface& i_semaphore = semaphore.get();
    // rsi::Filename filename = "data/exparx.webflow.zip";
    // i_semaphore.send(filename);
    // REQUIRE(extras::contains(i_semaphore.write(filename), client_dir));
    // Verify(Method(semaphore, send));
    // Verify(Method(semaphore, write));
    // clean();

    /**
     * @brief Mock<rsi::SemaphoreInterface> client_lock;
     *
     */
    Mock<rsi::SemaphoreInterface> client_lock;
    When(Method(client_lock, lock))
        .AlwaysDo(
            [&i_semaphore](const rsi::Lock& lock) {
                rsi::FileNotFoundException::assertion(lock, __INFO__);
                rsi::ParcelImploder parcelImploder;
                auto wrapped = parcelImploder.wrap(lock);
                rsi::FileNotFoundException::assertion(wrapped, __INFO__);
                i_semaphore.send(wrapped);
                return lock;
            });
    When(Method(client_lock, unlock))
        .AlwaysDo(
            [&i_semaphore](const rsi::Lock& lock) {
                auto status = i_semaphore.read_line();
                rsi::ParcelImploder parcelImploder;
                parcelImploder.clean(lock);
                std::cout << extras::pass(lock) << std::endl;
                std::cout << extras::pass(status) << std::endl;
                std::cout << extras::pass("send_file2 successful") << std::endl;
                return lock;
            });

    /**
     * @brief Mock<rsi::SemaphoreInterface> client_lock;
     *
     */
    Mock<rsi::SemaphoreInterface> server_lock;
    When(Method(server_lock, lock))
        .AlwaysDo(
            [&i_semaphore](const rsi::Lock& lock) {
                rsi::ParcelImploder parcelImploder;
                auto wrappedName = parcelImploder.wrapped(lock);
                return i_semaphore.write(wrappedName);
            });
    When(Method(server_lock, unlock))
        .AlwaysDo(
            [&i_semaphore](const rsi::Lock& lock) {
                rsi::ParcelImploder parcelImploder;
                parcelImploder.unWrap(lock);
                parcelImploder.merge(lock);
                auto original = parcelImploder.clean(lock);
                i_semaphore.send_line("uploader completed");
                std::cout << extras::pass(lock) << std::endl;
                std::cout << extras::pass("write_file successful") << std::endl;
                return original;
            });

    /**
     * @brief Uploader Client/Server mock
     *
     */
    rsi::SemaphoreInterface& i_client = client_lock.get();
    rsi::SemaphoreInterface& i_server = server_lock.get();

    prepare();

    auto client_filename = extras::replace_all(original, "data/", client_dir);
    auto server_filename = extras::replace_all(original, "data/", server_dir);

    REQUIRE(fs::exists("data/client/exparx.webflow.zip"));
    REQUIRE(!fs::exists("data/server/exparx.webflow.zip"));

    i_client.lock(client_filename);
    i_server.lock(server_filename);
    i_server.unlock(server_filename);
    i_client.unlock(client_filename);

    REQUIRE(fs::exists("data/client/exparx.webflow.zip"));
    REQUIRE(fs::exists("data/server/exparx.webflow.zip"));

    clean();

    Verify(Method(client_lock, lock));
    Verify(Method(client_lock, unlock));
    Verify(Method(server_lock, lock));
    Verify(Method(server_lock, unlock));


}
