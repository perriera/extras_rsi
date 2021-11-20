#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ParcelInterface: hexToBin", "[ParcelInterface]") {

    rsi::Parameter original = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");
    rsi::Parameter hexed = original + "_hexed";
    rsi::Parameter packed = original + "_packed";
    rsi::Parameter duplicate = original + "_unpacked";
    Mock<rsi::ParcelInterface> mock;
    When(Method(mock, original)).AlwaysReturn(original);
    When(Method(mock, hexed)).AlwaysReturn(hexed);
    When(Method(mock, packed)).AlwaysReturn(packed);
    When(Method(mock, duplicate)).AlwaysReturn(duplicate);

    When(Method(mock, pack))
        .AlwaysDo(
            [&original, &packed, &hexed]() {
                rsi::FileNotFoundException::assertion(original, __INFO__);
                std::ifstream inBin(original);
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
            [&packed, &duplicate, &hexed]() {
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
                std::ofstream outBin(duplicate);
                rsi::ConvertFile().convertToBin(inHex, outBin);
                outBin.close();
                rsi::FileNotFoundException::assertion(duplicate, __INFO__);
            }
    );

    When(Method(mock, verify_integrity))
        .AlwaysDo(
            [&original, &duplicate]() {
                rsi::FileNotFoundException::assertion(original, __INFO__);
                rsi::FileNotFoundException::assertion(duplicate, __INFO__);
                rsi::PackedException::assertion(original, duplicate, __INFO__);
                return true;
            }
    );

    if (fs::exists(packed))
        fs::remove(packed);
    if (fs::exists(hexed))
        fs::remove(hexed);
    if (fs::exists(duplicate))
        fs::remove(duplicate);

    rsi::ParcelInterface& i = mock.get();
    REQUIRE(i.original() == original);
    REQUIRE(i.hexed() == hexed);
    REQUIRE(i.packed() == packed);
    REQUIRE(i.duplicate() == duplicate);
    REQUIRE(fs::exists(i.original()));
    REQUIRE(!fs::exists(i.hexed()));
    REQUIRE(!fs::exists(i.packed()));
    REQUIRE(!fs::exists(i.duplicate()));
    i.pack();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.hexed()));
    REQUIRE(fs::exists(i.packed()));
    REQUIRE(!fs::exists(i.duplicate()));
    i.unpack();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.hexed()));
    REQUIRE(fs::exists(i.packed()));
    REQUIRE(fs::exists(i.duplicate()));
    i.verify_integrity();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.duplicate()));
    Verify(Method(mock, pack));
    Verify(Method(mock, unpack));
    Verify(Method(mock, verify_integrity));
}
