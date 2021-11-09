
#include <rsi/bin2hex/ConvertByte.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ConvertByteInterface", "[ConvertInterface]") {

    rsi::Hex hex = 'A';
    rsi::Byte btye = 'B';
    Mock<rsi::ConvertByteInterface> mock;
    When(Method(mock, hexToByte))
        .AlwaysDo(
            [](rsi::Hex cahr) {
                return rsi::Byte(cahr);
            });
    When(Method(mock, byteToHex))
        .AlwaysDo(
            [](const rsi::Byte btye) {
                return rsi::Hex(btye);
            });

    rsi::ConvertByteInterface& i = mock.get();
    REQUIRE(i.hexToByte(hex) == rsi::Byte(hex));
    REQUIRE(i.byteToHex(btye) == rsi::Hex(btye));
    Verify(Method(mock, hexToByte));
    Verify(Method(mock, byteToHex));
}
