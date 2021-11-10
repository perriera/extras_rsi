
#include <rsi/bin2hex/ConvertFile.hpp>
#include <iostream>
#include <fstream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ConvertFileInterface", "[ConvertInterface]") {

    Mock<rsi::ConvertFileInterface> mock;
    When(Method(mock, hexToBin))
        .AlwaysDo(
            [](const rsi::HexFile& hexFile) {
                rsi::BinFile binFile;
                rsi::ConvertLine converter;
                for (auto hexLine : hexFile) {
                    rsi::BinLine binline = converter.hexToBin(hexLine);
                    binFile.push_back(binline);
                }
                return binFile;
            });
    When(Method(mock, binToHex))
        .AlwaysDo(
            [](const rsi::BinFile& binFile) {
                rsi::HexFile hexFile;
                rsi::ConvertLine converter;
                for (auto binLine : binFile) {
                    rsi::HexLine hexline = converter.binToHex(binLine);
                    hexFile.push_back(hexline);
                }
                return hexFile;
            });

    rsi::HexFile hexFile;
    rsi::BinFile binFile;

    std::ifstream in("send.txt");
    REQUIRE(in.good());
    while (in.good()) {
        std::string line;
        getline(in, line);
        if (in.good())
            hexFile.push_back(line);
    }

    rsi::ConvertFileInterface& i = mock.get();
    binFile = i.hexToBin(hexFile);
    hexFile = i.binToHex(binFile);
    REQUIRE(i.hexToBin(hexFile) == binFile);
    REQUIRE(i.binToHex(binFile) == hexFile);
    Verify(Method(mock, hexToBin));
    Verify(Method(mock, binToHex));
}
