
#include <rsi/bin2hex/ConvertByte.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ConvertByteInterface", "[ConvertInterface]") {

    rsi::Hex hex = 'A';
    rsi::Byte btye = 0;
    Mock<rsi::ConvertByteInterface> mock;
    When(Method(mock, hexToByte))
        .AlwaysDo(
            [&btye](rsi::Hex cahr) {
                return btye;
            });
    When(Method(mock, byteToHex))
        .AlwaysDo(
            [&hex](const rsi::Byte btye) {
                return hex;
            });

    rsi::ConvertByteInterface& i = mock.get();
    REQUIRE(i.hexToByte(hex) == btye);
    REQUIRE(i.byteToHex(btye) == hex);
    Verify(Method(mock, hexToByte));
    Verify(Method(mock, byteToHex));
}
