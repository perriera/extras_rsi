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

SCENARIO("Test ParcelInterface: GOFUCKYOURSELF", "[ParcelInterface]") {

    rsi::Parameter parcel = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");

    rsi::Parcel packed(parcel);

    rsi::ParcelInterface& i = packed;
    REQUIRE(fs::exists(packed.parcel()));
    REQUIRE(fs::exists(packed.hexed()));
    REQUIRE(fs::exists(packed.packed()));
    REQUIRE(fs::exists(packed.unpacked()));
    i.verify_integrity();
    REQUIRE(fs::exists(packed.parcel()));
    REQUIRE(fs::exists(packed.unpacked()));
    i.clean();
    REQUIRE(fs::exists(packed.parcel()));
    REQUIRE(!fs::exists(packed.hexed()));
    REQUIRE(!fs::exists(packed.packed()));
    REQUIRE(!fs::exists(packed.unpacked()));
}
