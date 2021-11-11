#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
namespace fs = std::filesystem;

SCENARIO("Test ConvertFileInterface: hexToBin", "[ConvertInterface]") {

    rsi::HexFile hexFile;
    rsi::BinFile binFile;

    std::ifstream in(~Paths("data/send.txt"));
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

SCENARIO("Test ConvertFileInterface: saveHex", "[ConvertInterface]") {

    rsi::Filename b1 = ~extras::Paths("build/run-unittests-rsi");
    auto b2 = "/tmp/run-unittests-rsi";
    rsi::Filename h1 = ~extras::Paths("data/send.txt");
    auto h2 = "/tmp/send.txt";
    std::ifstream inBin(b1);
    REQUIRE(inBin.good());
    std::ifstream inHex(h1);
    REQUIRE(inHex.good());

    rsi::BinFile binFile;
    rsi::HexFile hexFile;

    rsi::ConvertFile converter;
    rsi::ConvertFileInterface& i = converter;
    binFile = i.loadBin(inBin, 40);
    hexFile = i.loadHex(inHex);
    {
        std::ofstream outBin(b2);
        REQUIRE(outBin.good());
        i.saveBin(outBin, binFile);
        std::ofstream outHex(h2);
        REQUIRE(outHex.good());
        i.saveHex(outHex, hexFile);
    }
    REQUIRE(fs::file_size(b1) == fs::file_size(b2));
    REQUIRE(fs::file_size(h1) + 1 == fs::file_size(h2));

}

SCENARIO("Test ConvertFileInterface: saveHex2", "[ConvertInterface]") {

    auto f1 = "build/run-unittests-rsi";
    auto f2 = "/tmp/run-unittests-rsi.txt";
    auto f3 = "/tmp/run-unittests-rsi";

    std::ifstream inBin(f1);
    REQUIRE(inBin.good());
    rsi::BinFile binFile;
    rsi::ConvertFile converter;
    binFile = converter.loadBin(inBin);
    {
        std::ofstream outHex(f2);
        REQUIRE(outHex.good());
        rsi::HexFile hexFile = converter.binToHex(binFile);
        converter.saveHex(outHex, hexFile);
    }

    std::ifstream inHex(f2);
    REQUIRE(inHex.good());
    rsi::HexFile hexFile = converter.loadHex(inHex);
    binFile = converter.hexToBin(hexFile);
    {
        std::ofstream outBin(f3);
        REQUIRE(outBin.good());
        converter.saveBin(outBin, binFile);
    }

    REQUIRE(fs::file_size(f1) == fs::file_size(f3));

    // std::string chmod = "chmod +x ";
    // chmod += f3;
    // system(chmod.c_str());
    // system(f3);

}
