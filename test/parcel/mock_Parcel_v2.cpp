#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/packed/Packed.hpp>
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

SCENARIO("Mock PackedInterface: hexToBin", "[PackedInterface]") {

    rsi::Parameter parcel = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");
    rsi::Parameter hexed = parcel + "_hexed";
    rsi::Parameter packed = parcel + "_packed";
    rsi::Parameter unpacked = parcel + "_unpacked";
    Mock<rsi::PackedInterface> mock;
    When(Method(mock, parcel)).Return(parcel);
    When(Method(mock, hexed)).Return(hexed);
    When(Method(mock, packed)).Return(packed);
    When(Method(mock, unpacked)).Return(unpacked);

    When(Method(mock, loadBin))
        .AlwaysDo(
            [&parcel](const rsi::Filename& filename) {
                rsi::FileNotFoundException::assertion(filename, __INFO__);
                std::ifstream in(filename);
                rsi::ConvertFile().loadBin(in);
                return rsi::ConvertFile().loadBin(in);;
            });

    When(Method(mock, hexFile))
        .AlwaysDo(
            [&packed]() {
                rsi::FileNotFoundException::assertion(packed, __INFO__);
                std::ifstream in(packed);
                rsi::HexFile hexFile;
                while (in.good()) {
                    rsi::PackedLine line;
                    in >> line;
                    if (in.good())
                        hexFile.push_back(line.hexLine());
                }
                return hexFile;
            });

    When(Method(mock, convertToHex))
        .AlwaysDo(
            [&parcel, &hexed]() {
                rsi::FileNotFoundException::assertion(parcel, __INFO__);
                std::ifstream inBin(parcel);
                std::ofstream outHex(hexed);
                return rsi::ConvertFile().convertToHex(inBin, outHex);
            });

    When(Method(mock, pack))
        .AlwaysDo(
            [&parcel, &packed, &hexed]() {
                rsi::FileNotFoundException::assertion(parcel, __INFO__);
                std::ifstream inBin(parcel);
                std::ofstream outHex(hexed);
                rsi::HexFile hexFile = rsi::ConvertFile().convertToHex(inBin, outHex);
                rsi::PackedFile packedFile;
                int cnt = 0;
                for (auto hexLine : hexFile) {
                    rsi::PackedLine packedLine(++cnt, hexLine);
                    packedFile.push_back(packedLine);
                }
                std::ofstream outPacked(packed);
                for (auto packedLine : packedFile)
                    outPacked << packedLine << std::endl;
                outPacked.close();
                rsi::FileNotFoundException::assertion(packed, __INFO__);

            });

    When(Method(mock, unpack))
        .AlwaysDo(
            [&packed, &unpacked, &hexed]() {
                rsi::FileNotFoundException::assertion(packed, __INFO__);
                std::ifstream in(packed);
                rsi::HexFile hexFile;
                while (in.good()) {
                    rsi::PackedLine line;
                    in >> line;
                    if (in.good())
                        hexFile.push_back(line.hexLine());
                }
                std::ofstream outHex(hexed);
                rsi::ConvertFile().saveHex(outHex, hexFile);
                outHex.close();
                std::ifstream inHex(hexed);
                std::ofstream outBin(unpacked);
                rsi::ConvertFile().convertToBin(inHex, outBin);
                outBin.close();
                rsi::FileNotFoundException::assertion(unpacked, __INFO__);
            }
    );

    When(Method(mock, verify_integrity))
        .AlwaysDo(
            [&parcel, &unpacked]() {
                rsi::FileNotFoundException::assertion(parcel, __INFO__);
                rsi::FileNotFoundException::assertion(unpacked, __INFO__);
                rsi::PackedException::assertion(parcel, unpacked, __INFO__);
            }
    );

    if (fs::exists(packed))
        fs::remove(packed);
    if (fs::exists(hexed))
        fs::remove(hexed);
    if (fs::exists(unpacked))
        fs::remove(unpacked);

    rsi::PackedInterface& i = mock.get();
    REQUIRE(i.parcel() == parcel);
    REQUIRE(i.hexed() == hexed);
    REQUIRE(i.packed() == packed);
    REQUIRE(i.unpacked() == unpacked);
    REQUIRE(fs::exists(parcel));
    REQUIRE(!fs::exists(hexed));
    REQUIRE(!fs::exists(packed));
    REQUIRE(!fs::exists(unpacked));
    REQUIRE(!fs::exists(unpacked));
    i.pack();
    i.unpack();
    i.verify_integrity();
    Verify(Method(mock, pack));
    Verify(Method(mock, unpack));
    Verify(Method(mock, verify_integrity));
}
