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

    rsi::Filename theCourier = "send_.txt";
    rsi::Filename binaryFile = "cplusplusorg.freeformjs.imploded.zip";

    rsi::Filename sourceFile = ~extras::Paths("data/" + binaryFile);
    REQUIRE(fs::exists(sourceFile));
    rsi::Filename theContent = "/tmp/" + binaryFile;
    auto setup_testdata = "cp " + sourceFile + " " + theContent;
    (void)system(setup_testdata.c_str());
    REQUIRE(fs::exists(theContent));

    Mock<rsi::VendorInterface> mock;
    When(Method(mock, theContent)).Return(theContent);
    When(Method(mock, theCourier)).Return(theCourier);
    When(Method(mock, wrapParcel))
        .AlwaysDo(
            [&theContent, &theCourier]() {
                std::ifstream inBin(theContent);
                REQUIRE(inBin.good());
                std::ofstream outHex(theCourier);
                REQUIRE(outHex.good());
                rsi::ConvertFile converter;
                converter.convertToHex(inBin, outHex);
            });
    When(Method(mock, deliverParcel))
        .AlwaysDo(
            [&theCourier]() {
                std::ifstream inHex(theCourier);
                REQUIRE(inHex.good());
                auto tmpFile = "/tmp/" + theCourier;
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
                auto rm_cmd = "rm " + theCourier;
                (void)system(rm_cmd.c_str());
                auto cp_cmd = "cp " + tmpFile + " " + theCourier;
                (void)system(cp_cmd.c_str());
            });
    When(Method(mock, unwrapParcel))
        .AlwaysDo(
            [&theContent, &theCourier]() {
                std::ifstream inHex(theCourier);
                REQUIRE(inHex.good());
                std::ofstream outBin(theContent);
                REQUIRE(outBin.good());
                rsi::ConvertFile converter;
                converter.convertToBin(inHex, outBin);
            });

    rsi::VendorInterface& i = mock.get();
    i.wrapParcel();
    i.deliverParcel();
    i.unwrapParcel();
    Verify(Method(mock, wrapParcel));
    Verify(Method(mock, deliverParcel));
    Verify(Method(mock, unwrapParcel));
}
