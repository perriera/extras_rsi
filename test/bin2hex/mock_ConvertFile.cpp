
#include <rsi/bin2hex/ConvertFile.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ConvertFileInterface", "[ConvertInterface]") {

    rsi::HexFile hexFile;
    rsi::BinFile binFile;
    Mock<rsi::ConvertFileInterface> mock;
    When(Method(mock, hexToBin))
        .AlwaysDo(
            [&binFile](const rsi::HexFile& hexFile) {

                return binFile;
            });
    When(Method(mock, binToHex))
        .AlwaysDo(
            [&hexFile](const rsi::BinFile& binFile) {
                return hexFile;
            });

    rsi::ConvertFileInterface& i = mock.get();
    REQUIRE(i.hexToBin(hexFile) == binFile);
    REQUIRE(i.binToHex(binFile) == hexFile);
    Verify(Method(mock, hexToBin));
    Verify(Method(mock, binToHex));
}
