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
    Mock<rsi::ParcelInterface> mock;
    When(Method(mock, payload)).Return(payload);
    When(Method(mock, parcel)).Return(parcel);
    When(Method(mock, pack))
        .AlwaysDo(
            [&payload, &parcel]() {
                rsi::FileNotFoundException::assertion(payload, __INFO__);
                std::ifstream inBin(payload);
                std::ofstream outHex(parcel);
                rsi::ConvertFile converter;
                // rsi::HexFile HexFile = converter.convertToHex(inBin, outHex);
                // for (auto hexLine : hexFile) {
                //     rsi::BinLine binline = converter.hexToBin(hexLine);
                //     binFile.push_back(binline);
                // }
                // return binFile;
            });
    When(Method(mock, unpack))
        .AlwaysDo(
            []() {
                // rsi::HexFile hexFile;
                // rsi::ConvertLine converter;
                // for (auto binLine : binFile) {
                //     rsi::HexLine hexline = converter.binToHex(binLine);
                //     hexFile.push_back(hexline);
                // }
                // return hexFile;
            });

    REQUIRE(fs::exists(payload));
    rsi::HexFile hexFile;
    rsi::BinFile binFile;


    // rsi::ConvertFileInterface& i = mock.get();
    // binFile = i.hexToBin(hexFile);
    // hexFile = i.binToHex(binFile);
    // REQUIRE(i.hexToBin(hexFile) == binFile);
    // REQUIRE(i.binToHex(binFile) == hexFile);
    // Verify(Method(mock, hexToBin));
    // Verify(Method(mock, binToHex));
}
