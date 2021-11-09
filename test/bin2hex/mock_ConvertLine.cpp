
#include <rsi/bin2hex/ConvertLine.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ConvertLineInterface", "[ConvertInterface]") {

    const char* argv[] = { "socketclient", "127.0.0.1", "8080",
                            "send.txt",     "convert",   "download" };
    rsi::HexLine hexLine = "this expression";
    rsi::BinLine binLine;
    Mock<rsi::ConvertLineInterface> mock;
    When(Method(mock, hexToBin))
        .AlwaysDo(
            [&binLine](const rsi::HexLine& hexLine) {

                return binLine;
            });
    When(Method(mock, binToHex))
        .AlwaysDo(
            [&hexLine](const rsi::BinLine& binLine) {
                return hexLine;
            });

    rsi::ConvertLineInterface& i = mock.get();
    REQUIRE(i.hexToBin(hexLine) == binLine);
    REQUIRE(i.binToHex(binLine) == hexLine);
    Verify(Method(mock, hexToBin));
    Verify(Method(mock, binToHex));
}
