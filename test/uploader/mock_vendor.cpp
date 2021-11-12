#include <rsi/uploader/Vendor.hpp>
#include <rsi/bin2hex/ConvertFile.hpp>
#include <extras/filesystem/paths.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock VendorInterface", "[VendorInterface]") {

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

    Mock<rsi::VendorInterface> mock;
    When(Method(mock, wrapParcel))
        .AlwaysDo(
            [&thePayload, &theParcel]() {
                std::ifstream inBin(thePayload);
                REQUIRE(inBin.good());
                std::ofstream outHex(theParcel);
                REQUIRE(outHex.good());
                rsi::ConvertFile converter;
                converter.convertToHex(inBin, outHex);
            });
    When(Method(mock, deliverParcel))
        .AlwaysDo(
            [&theParcel]() {
                std::ifstream inHex(theParcel);
                REQUIRE(inHex.good());
                auto tmpFile = "/tmp/" + theParcel;
                std::ofstream outHex(tmpFile);
                REQUIRE(outHex.good());
                while (inHex.good()) {
                    char c;
                    inHex >> std::noskipws >> c;
                    if (c == '\n') {
                        outHex << std::endl;
                        continue;
                    }
                    if (c + 1 > 'f') c = '0';
                    else if (c + 1 > '9') c = 'a';
                    else c++;
                    outHex << c;
                }
                outHex.close();
                auto rm_cmd = "rm " + theParcel;
                (void)system(rm_cmd.c_str());
                auto cp_cmd = "cp " + tmpFile + " " + theParcel;
                (void)system(cp_cmd.c_str());
            });
    When(Method(mock, unwrapParcel))
        .AlwaysDo(
            [&thePayload, &theParcel]() {
                std::ifstream inHex(theParcel);
                REQUIRE(inHex.good());
                std::ofstream outBin(thePayload);
                REQUIRE(outBin.good());
                rsi::ConvertFile converter;
                converter.convertToBin(inHex, outBin);
                fs::remove(theParcel);
            });

    rsi::VendorInterface& i = mock.get();

    REQUIRE(fs::exists(thePayload));
    REQUIRE(!fs::exists(theParcel));
    i.wrapParcel();
    REQUIRE(fs::exists(thePayload));
    REQUIRE(fs::exists(theParcel));
    i.deliverParcel();
    i.unwrapParcel();
    REQUIRE(fs::exists(thePayload));
    REQUIRE(!fs::exists(theParcel));

    // 


    Verify(Method(mock, wrapParcel));
    Verify(Method(mock, deliverParcel));
    Verify(Method(mock, unwrapParcel));
}
