#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <rsi/exceptions.hpp>

#include "../unittesting/catch.hpp"

using namespace extras;
namespace fs = std::filesystem;

SCENARIO("Test ParcelInterface: hexToBin", "[ParcelInterface]") {

    rsi::Parameter payloadName = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");
    rsi::Parameter parcelName = "/tmp/parcel.txt";
    rsi::ParcelFile parcelFile;

    if (fs::exists(parcelName))
        fs::remove(parcelName);

    rsi::Parcel parcel(payloadName, parcelName);
    rsi::ParcelInterface& i = parcel;

    REQUIRE(fs::exists(payloadName));
    REQUIRE(!fs::exists(parcelName));
    i.pack();

    REQUIRE(fs::exists(parcelName));
    if (fs::exists(i.payload_unpacked()))
        fs::remove(i.payload_unpacked());
    REQUIRE(!fs::exists(i.payload_unpacked()));
    i.unpack();
    REQUIRE(fs::exists(i.payload_unpacked()));
    i.compare();
    i.check_packaging();
}
