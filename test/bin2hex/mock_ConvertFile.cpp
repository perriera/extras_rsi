
#include <rsi/bin2hex/ConvertFile.hpp>
#include <iostream>
#include <fstream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ConvertFileInterface: hexToBin", "[ConvertInterface]") {

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

SCENARIO("Mock ConvertFileInterface: loadBin", "[ConvertInterface]") {

    Mock<rsi::ConvertFileInterface> mock;
    When(Method(mock, loadBin))
        .AlwaysDo(
            [](std::istream& in, int columns) {
                rsi::BinFile binFile;
                rsi::ConvertLine converter;
                while (in.good()) {
                    rsi::BinLine line;
                    for (int i = 0; i < columns && in.good();i++) {
                        byte b = 0;
                        in >> std::noskipws >> b;
                        if (in.good())
                            line.push_back(b);
                    }
                    binFile.push_back(line);
                }
                return binFile;
            });

    When(Method(mock, loadHex))
        .AlwaysDo(
            [](std::istream& in) {
                rsi::HexFile hexFile;
                rsi::ConvertLine converter;
                while (in.good()) {
                    rsi::HexLine line;
                    getline(in, line);
                    if (in.good())
                        hexFile.push_back(line);
                }
                return hexFile;
            });

    rsi::BinFile binFile;
    rsi::HexFile hexFile;

    std::ifstream inBin("build/run-unittests-rsi");
    REQUIRE(inBin.good());
    std::ifstream inHex("send.txt");
    REQUIRE(inHex.good());

    rsi::ConvertFileInterface& i = mock.get();
    binFile = i.loadBin(inBin, 40);
    hexFile = i.loadHex(inHex);
    Verify(Method(mock, loadBin));
    Verify(Method(mock, loadHex));
}
