#include <rsi/uploader/Vendor.hpp>
#include <extras/strings.hpp>
#include <extras/filesystem/paths.hpp>
#include <filesystem>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
namespace fs = std::filesystem;

SCENARIO("Test VendorInterface", "[VendorInterface]") {

    rsi::Filename thePayload;
    {
        rsi::Filename theSource = "cplusplusorg.freeformjs.imploded.zip";
        rsi::Filename sourceFile = ~extras::Paths("data/" + theSource);
        REQUIRE(fs::exists(sourceFile));
        thePayload = "/tmp/" + theSource;
        auto setup_testdata = "cp " + sourceFile + " " + thePayload;
        (void)system(setup_testdata.c_str());
    }
    rsi::Filename theParcel = "send.txt";
    if (fs::exists(theParcel))
        fs::remove(theParcel);

    const char* argv[] = {
        "socketclient", thePayload.c_str(),  "127.0.0.1", "8080",
        "vendor",   "download" };
    int argc = 6;

    rsi::VendorClient testUnit;
    testUnit.parameters(argc, argv);
    rsi::VendorInterface& i = testUnit;

    // wrap parcel
    REQUIRE(fs::exists(testUnit.parcel()));
    REQUIRE(fs::exists(testUnit.payload()));
    i.wrapParcel();

    // deliver parcel
    REQUIRE(fs::exists(testUnit.parcel()));
    fs::remove(testUnit.payload());
    REQUIRE(!fs::exists(testUnit.payload()));
    i.deliverParcel();
    REQUIRE(fs::exists(testUnit.payload()));
    fs::remove(testUnit.payload());
    REQUIRE(!fs::exists(testUnit.payload()));

    // un parcel
    i.unwrapParcel();
    REQUIRE(fs::exists(testUnit.payload()));
}
