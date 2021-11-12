#include <rsi/bin2hex/ConvertLine.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;

SCENARIO("Test ConvertLineInterface", "[ConvertInterface]") {

    rsi::ConvertLine converter;
    rsi::ConvertLineInterface& i = converter;
    rsi::BinLine binLine = { 'a', 'b', 'c' };
    rsi::HexLine hexLine = i.binToHex(binLine);
    REQUIRE(i.hexToBin(hexLine) == binLine);
    REQUIRE(i.binToHex(binLine) == hexLine);
}
