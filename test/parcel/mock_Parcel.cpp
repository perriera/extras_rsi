#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <rsi/exceptions.hpp>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ParcelInterface: hexToBin", "[ParcelInterface]") {

    rsi::Parameter payload = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");
    rsi::Parameter parcel = "/tmp/parcel.txt";
    rsi::ParcelFile parcelFile;
    Mock<rsi::ParcelInterface> mock;
    When(Method(mock, payload)).Return(payload);
    When(Method(mock, parcel)).Return(parcel);
    When(Method(mock, pack))
        .AlwaysDo(
            [&payload, &parcel, &parcelFile]() {
                rsi::FileNotFoundException::assertion(payload, __INFO__);
                std::ifstream inBin(payload);
                rsi::HexFile hexFile;
                {
                    std::ofstream outHex(parcel);
                    rsi::ConvertFile converter;
                    hexFile = converter.convertToHex(inBin, outHex);
                }
                std::ofstream outHex(parcel);
                int cnt = 0;
                for (auto hexLine : hexFile)
                    parcelFile.push_back(rsi::ParcelLine(++cnt, hexLine));
                {
                    std::ofstream outHex(parcel);
                    for (auto line : parcelFile)
                        outHex << line << std::endl;
                }
                rsi::ParcelFile parcelFile2;
                {
                    std::ifstream inHex(parcel);
                    int cnt = 0;
                    while (inHex.good()) {
                        rsi::ParcelLine line;
                        inHex >> line;
                        if (!inHex.good())
                            break;
                        parcelFile2.push_back(line);
                        rsi::ParcelLineException::assertion(++cnt, line.lineNo(), __INFO__);
                    }
                }
                for (long unsigned int i = 0; i < parcelFile.size(); i++)
                    REQUIRE(parcelFile[i] == parcelFile2[i]);
            });

    When(Method(mock, unpack))
        .AlwaysDo(
            [&payload, &parcel]() {
                rsi::FileNotFoundException::assertion(parcel, __INFO__);
                rsi::ParcelFile parcelFile;
                {
                    std::ifstream inHex(parcel);
                    int cnt = 0;
                    while (inHex.good()) {
                        rsi::ParcelLine line;
                        inHex >> line;
                        if (!inHex.good())
                            break;
                        parcelFile.push_back(line);
                        rsi::ParcelLineException::assertion(++cnt, line.lineNo(), __INFO__);
                    }
                }
                //
                rsi::Parameter hexFilename = parcel + "_hex.txt";
                {
                    rsi::HexFile hexFile;
                    for (auto parcelLine : parcelFile)
                        hexFile.push_back(parcelLine.hexLine());
                    rsi::ConvertFile converter;
                    std::ofstream outHex(hexFilename);
                    converter.saveHex(outHex, hexFile);
                }
                //
                std::ifstream inBin(payload);
                rsi::ConvertFile converter;
                rsi::BinFile original = converter.loadBin(inBin);
                rsi::BinFile duplicate;
                {
                    rsi::ConvertFile converter;
                    std::ifstream inHex(hexFilename);
                    std::ofstream outBin(payload + ".unpacked");
                    duplicate = converter.convertToBin(inHex, outBin);
                }
                for (long unsigned int i = 0; i < original.size(); i++)
                    REQUIRE(original[i] == duplicate[i]);
            }
    );

    REQUIRE(fs::exists(payload));

    rsi::ParcelInterface& i = mock.get();
    i.pack();
    i.unpack();
    Verify(Method(mock, pack));
}
