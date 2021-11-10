
#include <rsi/bin2hex/ConvertFile.hpp>
#include <iostream>
#include <fstream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;

SCENARIO("Test ConvertFileInterface", "[ConvertInterface]") {

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

    rsi::ConvertFile converter;
    rsi::ConvertFileInterface& i = converter;
    binFile = i.hexToBin(hexFile);
    hexFile = i.binToHex(binFile);
    REQUIRE(i.hexToBin(hexFile) == binFile);
    REQUIRE(i.binToHex(binFile) == hexFile);
}
