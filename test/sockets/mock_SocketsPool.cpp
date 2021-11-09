
#include <rsi/sockets/Pool.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock SocketPoolInterface", "[SocketPoolInterface]") {

    Mock<rsi::SocketPoolInterface> mock;
    When(Method(mock, transfer))
        .AlwaysDo(
            []() {
            });

    rsi::SocketPoolInterface& i = mock.get();
    i.transfer();
    Verify(Method(mock, transfer));
}
