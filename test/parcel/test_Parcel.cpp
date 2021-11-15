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

SCENARIO("Test ParcelInterface: hexToBin", "[ParcelInterface]") {

    rsi::Parameter parcel = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");

    rsi::Parcel packed(parcel);

    if (fs::exists(packed.packed()))
        fs::remove(packed.packed());
    if (fs::exists(packed.hexed()))
        fs::remove(packed.hexed());
    if (fs::exists(packed.unpacked()))
        fs::remove(packed.unpacked());

    rsi::ParcelInterface& i = packed;
    REQUIRE(i.parcel() == packed.parcel());
    REQUIRE(i.hexed() == packed.hexed());
    REQUIRE(i.packed() == packed.packed());
    REQUIRE(i.unpacked() == packed.unpacked());
    REQUIRE(fs::exists(packed.parcel()));
    REQUIRE(!fs::exists(packed.hexed()));
    REQUIRE(!fs::exists(packed.packed()));
    REQUIRE(!fs::exists(packed.unpacked()));
    i.pack();
    REQUIRE(fs::exists(packed.parcel()));
    REQUIRE(fs::exists(packed.hexed()));
    REQUIRE(fs::exists(packed.packed()));
    REQUIRE(!fs::exists(packed.unpacked()));
    i.unpack();
    REQUIRE(fs::exists(packed.parcel()));
    REQUIRE(fs::exists(packed.hexed()));
    REQUIRE(fs::exists(packed.packed()));
    REQUIRE(fs::exists(packed.unpacked()));
    REQUIRE(i.verify_integrity());
    REQUIRE(fs::exists(packed.parcel()));
    REQUIRE(fs::exists(packed.unpacked()));
    i.clean();
    REQUIRE(fs::exists(packed.parcel()));
    REQUIRE(!fs::exists(packed.hexed()));
    REQUIRE(!fs::exists(packed.packed()));
    REQUIRE(!fs::exists(packed.unpacked()));
}
