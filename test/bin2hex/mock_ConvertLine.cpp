
#include <rsi/bin2hex/ConvertLine.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ConvertLineInterface", "[ConvertInterface]") {

    Mock<rsi::ConvertLineInterface> mock;
    When(Method(mock, hexToBin))
        .AlwaysDo(
            [](const rsi::HexLine& hexLine) {
                rsi::BinLine binLine = rsi::hexToBytes(hexLine);
                return binLine;
            });
    When(Method(mock, binToHex))
        .AlwaysDo(
            [](const rsi::BinLine& binLine) {
                rsi::HexLine hexLine = rsi::bytesToHex(binLine);
                return hexLine;
            });

    rsi::ConvertLineInterface& i = mock.get();
    rsi::BinLine binLine = { 'a', 'b', 'c' };
    rsi::HexLine hexLine = i.binToHex(binLine);
    REQUIRE(i.hexToBin(hexLine) == binLine);
    REQUIRE(i.binToHex(binLine) == hexLine);
    Verify(Method(mock, hexToBin));
    Verify(Method(mock, binToHex));
}
