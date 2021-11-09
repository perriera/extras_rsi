
#include <rsi/sockets/Parameters.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock SocketPoolParametersInterface", "[SocketPoolParametersInterface]") {

    const char* argv[] = { "socketclient", "127.0.0.1", "8080",
                            "send.txt",     "convert",   "download" };
    int argc = 6;
    Mock<rsi::SocketPoolParametersInterface> mock;
    When(Method(mock, parameters))
        .AlwaysDo(
            [](int argc, char const* argv[]) {
                return rsi::Parameters();
            });

    rsi::SocketPoolParametersInterface& i = mock.get();
    REQUIRE(i.parameters(argc, argv) == rsi::Parameters());
    Verify(Method(mock, parameters));
}
