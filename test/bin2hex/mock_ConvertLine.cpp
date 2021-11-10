
#include <rsi/bin2hex/ConvertLine.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

int char2int(char input)
{
    if (input >= '0' && input <= '9')
        return input - '0';
    if (input >= 'A' && input <= 'F')
        return input - 'A' + 10;
    if (input >= 'a' && input <= 'f')
        return input - 'a' + 10;
    throw std::invalid_argument("Invalid input string");
}

// This function assumes src to be a zero terminated sanitized string with
// an even number of [0-9a-f] characters, and target to be sufficiently large
rsi::BinLine  hex2bin(const rsi::HexLine& src)
{
    rsi::BinLine result;
    if ((src.length() % 2) != 1)
        throw "Invalud source";
    for (int i = 0; i < src.length(); i += 2)
    {
        byte value = char2int(src[i]) * 16 + char2int(src[i + 1]);
        result.push_back(value);
    }
    return result;
}

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
