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
    MockedVendor(const rsi::Filename& theContent)
        : rsi::VendorClient(theContent) {
    }
    virtual void transfer()  override {
        auto uploaded_file =
            extras::replace_all(theCourier(), ".txt", "_uploaded.txt");
        auto copy_cmd = "cp " + theCourier() + " " + uploaded_file;
        (void)system(copy_cmd.c_str());
    }

};

SCENARIO("Test VendorInterface", "[VendorInterface]") {

    const char* argv[] = {
        "socketclient", "send.txt",  "127.0.0.1", "8080",
        "convert",   "download" };
    int argc = 6;

    rsi::Filename theCourier = "send_.txt";
    rsi::Filename binaryFile = "cplusplusorg.freeformjs.imploded.zip";
    rsi::Filename sourceFile = ~extras::Paths("data/" + binaryFile);
    REQUIRE(fs::exists(sourceFile));
    rsi::Filename theContent = "/tmp/" + binaryFile;
    auto setup_testdata = "cp " + sourceFile + " " + theContent;
    (void)system(setup_testdata.c_str());
    REQUIRE(fs::exists(theContent));

    MockedVendor testUnit(theContent);
    testUnit.parameters(argc, argv);
    rsi::VendorInterface& i = testUnit;

    i.wrapParcel();
    testUnit.transfer();
    i.deliverParcel();
    i.unwrapParcel();
}
