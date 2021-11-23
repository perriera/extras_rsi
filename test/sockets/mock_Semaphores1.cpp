#include <rsi/sockets/Semaphores.hpp>
#include <rsi/uploader/Uploader.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock SemaphoreInterface: Uploader", "[SemaphoreInterface]") {

    Mock<rsi::SemaphoreInterface> sema;
    Mock<rsi::UploaderInterface> uploader;

    rsi::Lock locked = "hello";

    When(Method(sema, lock))
        .AlwaysDo(
            [](const rsi::Lock& lock) {
                return lock;
            });
    When(Method(sema, unlock))
        .AlwaysDo(
            [](const rsi::Lock& lock) {
                return lock;
            });

    rsi::SemaphoreInterface& i_sema = sema.get();

    When(Method(uploader, transfer))
        .AlwaysDo(
            [&i_sema]() {
                rsi::Lock lock;
                i_sema.unlock(i_sema.lock(lock));
            });

    i_sema.lock(i_sema.unlock(locked));
    i_sema.unlock(i_sema.lock(locked));
    Verify(Method(sema, lock));
    Verify(Method(sema, unlock));

    rsi::UploaderInterface& i_uploader = uploader.get();
    i_uploader.transfer();
    Verify(Method(uploader, transfer));


}
