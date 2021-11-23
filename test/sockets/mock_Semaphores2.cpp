#include <rsi/sockets/Semaphores.hpp>
#include <rsi/uploader/Uploader.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock SemaphoreInterface: lock/unlock", "[SemaphoreInterface]") {

    /**
     * @brief Mock<rsi::UploaderInterface> uploader;
     *
     */
    Mock<rsi::UploaderInterface> uploader;
    When(Method(uploader, send))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
            });
    When(Method(uploader, write))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                return filename;
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
            [&i_uploader](const rsi::Lock& lock) {
                i_uploader.send(lock);
                return lock;
            });
    When(Method(semaphore, unlock))
        .AlwaysDo(
            [&i_uploader](const rsi::Lock& lock) {
                return i_uploader.write(lock);;
            });

    rsi::SemaphoreInterface& i_sema = semaphore.get();
    i_sema.lock(i_sema.unlock(filename));
    i_sema.unlock(i_sema.lock(filename));
    Verify(Method(semaphore, lock));
    Verify(Method(semaphore, unlock));


}
