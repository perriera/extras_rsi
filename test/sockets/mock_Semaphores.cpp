#include <rsi/sockets/Semaphores.hpp>
#include <rsi/uploader/Uploader.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock SemaphoreInterface", "[SemaphoreInterface]") {

    Mock<rsi::SemaphoreInterface> mock;
    When(Method(mock, lock))
        .AlwaysDo(
            [](const rsi::Lock& lock) {
                return lock;
            });
    When(Method(mock, unlock))
        .AlwaysDo(
            [](const rsi::Lock& lock) {
                return lock;
            });

    rsi::SemaphoreInterface& i = mock.get();
    i.lock(i.unlock(""));
    i.unlock(i.lock(""));
    Verify(Method(mock, lock));
    Verify(Method(mock, unlock));
}
