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
static std::string original = ~extras::Paths("data/exparx.webflow.zip");

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

SCENARIO("Mock SemaphoreInterface: Downloader", "[SemaphoreInterface]") {

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
                if (!fs::exists(client_dir)) {
                    SystemException::assertion("mkdir " + client_dir, __INFO__);
                }
                if (internet.size() == 0)
                    throw "Nothing to save";
                auto target = extras::replace_all(filename, "data/", client_dir);
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

    rsi::UploaderInterface& i_semaphore = semaphore.get();
    rsi::Filename filename = "data/exparx.webflow.zip";
    i_semaphore.send(filename);
    REQUIRE(extras::contains(i_semaphore.write(filename), client_dir));
    Verify(Method(semaphore, send));
    Verify(Method(semaphore, write));

    /**
     * @brief Mock<rsi::SemaphoreInterface> client_lock;
     *
     */
    Mock<rsi::SemaphoreInterface> client_lock;
    When(Method(client_lock, lock))
        .AlwaysDo(
            [&i_semaphore](const rsi::Lock& filename) {
                rsi::FileNotFoundException::assertion(filename, __INFO__);
                rsi::ParcelImploder parcelImploder;
                auto wrapped = parcelImploder.wrap(filename);
                rsi::FileNotFoundException::assertion(wrapped, __INFO__);
                i_semaphore.send(wrapped);
                parcelImploder.clean(filename);
                return filename;
            });
    When(Method(client_lock, unlock))
        .AlwaysDo(
            [&i_semaphore](const rsi::Lock& filename) {
                auto status = i_semaphore.read_line();
                std::cout << extras::pass(filename) << std::endl;
                std::cout << extras::pass(status) << std::endl;
                std::cout << extras::pass("send_file2 successful") << std::endl;
                return filename;
            });

    /**
     * @brief Mock<rsi::SemaphoreInterface> client_lock;
     *
     */
    Mock<rsi::SemaphoreInterface> server_lock;
    When(Method(server_lock, lock))
        .AlwaysDo(
            [&i_semaphore](const rsi::Lock& filename) {
                static std::string server_dir = "data/server/";
                rsi::ParcelImploder parcelImploder;
                auto wrappedName = parcelImploder.wrapped(filename);
                return i_semaphore.write(wrappedName);
            });
    When(Method(server_lock, unlock))
        .AlwaysDo(
            [&i_semaphore](const rsi::Lock& filename) {
                auto fn = extras::replace_all(filename, "data/", client_dir);
                rsi::ParcelImploder parcelImploder;
                parcelImploder.unWrap(fn);
                parcelImploder.merge(fn);
                auto original = parcelImploder.clean(fn);
                i_semaphore.send_line("uploader completed");
                std::cout << extras::pass(fn) << std::endl;
                std::cout << extras::pass("write_file successful") << std::endl;
                return original;
            });

    /**
     * @brief Uploader Client/Server mock
     *
     */
    rsi::SemaphoreInterface& i_client = client_lock.get();
    rsi::SemaphoreInterface& i_server = server_lock.get();

    clean();

    i_server.lock(i_client.lock(filename));
    i_client.unlock(i_server.unlock(filename));

    clean();

    Verify(Method(client_lock, lock));
    Verify(Method(client_lock, unlock));
    Verify(Method(server_lock, lock));
    Verify(Method(server_lock, unlock));


}
