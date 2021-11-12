#include <rsi/vendor/Vendor.hpp>
#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/exceptions.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
namespace fs = std::filesystem;



SCENARIO("Test ConvertFileInterface (accuracy)", "[Hex2Bin]") {

    rsi::Filename thePayload;
    {
        rsi::Filename theSource = "cplusplusorg.freeformjs.imploded.zip";
        rsi::Filename sourceFile = ~extras::Paths("data/" + theSource);
        REQUIRE(fs::exists(sourceFile));
        thePayload = "/tmp/" + theSource;
        auto setup_testdata = "cp " + sourceFile + " " + thePayload;
        (void)system(setup_testdata.c_str());
    }

    const char* argv[] = {
        "vendor_client", thePayload.c_str(),  "127.0.0.1", "8080" };
    int argc = 4;

    rsi::VendorClient testUnit;
    testUnit.parameters(argc, argv);

    rsi::Filename theParcel = testUnit.payload_uploaded();
    if (fs::exists(theParcel))
        fs::remove(theParcel);

    {
        rsi::FileNotFoundException::assertion(testUnit.payload(), __INFO__);
        std::ifstream inBin(testUnit.payload());
        std::ofstream outHex(testUnit.parcel());
        rsi::ConvertFile converter;
        converter.convertToHex(inBin, outHex);
    }
    {
        rsi::FileNotFoundException::assertion(testUnit.parcel(), __INFO__);
        std::ifstream inHex(testUnit.parcel());
        std::ofstream outBin(testUnit.payload() + "_duplicate");
        rsi::ConvertFile converter;
        converter.convertToBin(inHex, outBin);
    }
    {
        rsi::ConvertFile converter;
        std::ifstream before(testUnit.payload());
        std::ifstream after(testUnit.payload() + "_duplicate");
        rsi::BinFile a = converter.loadBin(before);
        rsi::BinFile b = converter.loadBin(after);
        REQUIRE(a == b);
    }

}
