#include <rsi/sockets/Semaphores.hpp>
#include <rsi/uploader/Uploader.hpp>
#include <rsi/parcel/Wrap.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/status/StatusLine.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/system.hpp>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

static std::string client_dir = "data/client/";
static std::string server_dir = "data/server/";
static std::string original = ~extras::Paths("data/exparx.webflow.zip");
static rsi::BinFile internet;

static void clean() {
    rsi::Parcel parcel(original);
    parcel.clean();
    rsi::ParcelImploder parcelImploder;
    parcelImploder.clean(original);
    if (fs::exists(client_dir)) {
        fs::remove_all(client_dir);
        SystemException::assertion("mkdir " + client_dir, __INFO__);
    }
    if (fs::exists(server_dir)) {
        fs::remove_all(server_dir);
        SystemException::assertion("mkdir " + server_dir, __INFO__);
    }
}

SCENARIO("Mock SemaphoreInterface: lock/unlock", "[SemaphoreInterface]") {

    clean();

    /**
     * @brief Mock<rsi::UploaderInterface> uploader;
     *
     */
    std::string internet;

    Mock<rsi::UploaderInterface> uploader;
    When(Method(uploader, send))
        .AlwaysDo(
            [&internet](const rsi::Filename& filename) {
                internet = filename;
            });
    When(Method(uploader, write))
        .AlwaysDo(
            [&internet](const rsi::Filename& filename) {
                internet.clear();
                return filename;
            });
    When(Method(uploader, send_line))
        .AlwaysDo(
            [&internet](const rsi::UploaderStatus& msg) {
                internet = msg;
            });
    When(Method(uploader, read_line))
        .AlwaysDo(
            [&internet]() {
                auto msg = internet;
                internet.clear();
                return msg;
            });

    rsi::UploaderInterface& i_uploader = uploader.get();
    rsi::Filename filename = "data/exparx.webflow.zip";
    i_uploader.send(filename);
    filename = i_uploader.write(filename);
    Verify(Method(uploader, send));
    Verify(Method(uploader, write));

    /**
     * @brief Mock<rsi::SemaphoreInterface> semaphore;
     *
     */
    Mock<rsi::SemaphoreInterface> semaphore;
    When(Method(semaphore, lock))
        .AlwaysDo(
            [&i_uploader](const rsi::Lock& filename) {
                rsi::FileNotFoundException::assertion(filename, __INFO__);
                rsi::ParcelImploder parcelImploder;
                auto wrapped = parcelImploder.wrap(filename);
                rsi::FileNotFoundException::assertion(wrapped, __INFO__);
                i_uploader.send(wrapped);
                return wrapped;
            });
    When(Method(semaphore, unlock))
        .AlwaysDo(
            [&i_uploader](const rsi::Lock& filename) {
                auto status = i_uploader.read_line();
                std::cout << extras::pass(filename) << std::endl;
                std::cout << extras::pass(status) << std::endl;
                std::cout << extras::pass("send_file2 successful") << std::endl;
                return i_uploader.write(filename);
            });

    rsi::SemaphoreInterface& i_sema = semaphore.get();
    i_sema.unlock(i_sema.lock(filename));
    Verify(Method(semaphore, lock));
    Verify(Method(semaphore, unlock));


}
