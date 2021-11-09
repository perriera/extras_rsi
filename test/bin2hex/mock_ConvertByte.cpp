
#include <rsi/bin2hex/ConvertByte.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ConvertByteInterface", "[ConvertInterface]") {

    const char* argv[] = { "socketclient", "127.0.0.1", "8080",
                            "send.txt",     "convert",   "download" };
    rsi::Char cahr = 'A';
    rsi::Byte btye = 0x65;
    Mock<rsi::ConvertByteInterface> mock;
    When(Method(mock, charToByte))
        .AlwaysDo(
            [&btye](rsi::Char cahr) {
                return btye;
            });
    When(Method(mock, byteToChar))
        .AlwaysDo(
            [&cahr](const rsi::Byte btye) {
                return cahr;
            });

    rsi::ConvertByteInterface& i = mock.get();
    REQUIRE(i.charToByte(cahr) == btye);
    REQUIRE(i.byteToChar(btye) == cahr);
    Verify(Method(mock, charToByte));
    Verify(Method(mock, byteToChar));
}
