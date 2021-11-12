#include <rsi/uploader/Vendor.hpp>
#include <extras/strings.hpp>
#include <extras/filesystem/paths.hpp>
#include <filesystem>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
namespace fs = std::filesystem;

class MockedVendor extends rsi::VendorClient {
public:
    virtual void transfer()  override {
        auto copy_cmd = "cp " + payload() + " " + payload_uploaded();
        (void)system(copy_cmd.c_str());
    }

};

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

    MockedVendor testUnit;
    testUnit.parameters(argc, argv);
    rsi::VendorInterface& i = testUnit;

    i.wrapParcel();
    REQUIRE(fs::exists(testUnit.payload()));
    testUnit.transfer();
    REQUIRE(fs::exists(testUnit.payload_uploaded()));
    i.deliverParcel();
    REQUIRE(!fs::exists(testUnit.payload_uploaded()));
    REQUIRE(fs::exists(testUnit.payload()));
    i.unwrapParcel();
}
