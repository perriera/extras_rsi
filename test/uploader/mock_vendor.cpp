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

    rsi::Filename transitFile = "send_.txt";
    rsi::Filename binaryFile = "cplusplusorg.freeformjs.imploded.zip";

    rsi::Filename sourceFile = ~extras::Paths("data/" + binaryFile);
    REQUIRE(fs::exists(sourceFile));
    rsi::Filename targetFile = "/tmp/" + binaryFile;
    auto setup_testdata = "cp " + sourceFile + " " + targetFile;
    (void)system(setup_testdata.c_str());
    REQUIRE(fs::exists(targetFile));

    Mock<rsi::VendorInterface> mock;
    When(Method(mock, addContent))
        .AlwaysDo(
            [&targetFile](const rsi::Filename& transitFile) {
                std::ifstream inBin(targetFile);
                REQUIRE(inBin.good());
                std::ofstream outHex(transitFile);
                REQUIRE(outHex.good());
                rsi::ConvertFile converter;
                converter.convertToHex(inBin, outHex);
            });
    When(Method(mock, changeContent))
        .AlwaysDo(
            [](const rsi::Filename& transitFile) {
                std::ifstream inHex(transitFile);
                REQUIRE(inHex.good());
                auto tmpFile = "/tmp/" + transitFile;
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
                auto rm_cmd = "rm " + transitFile;
                (void)system(rm_cmd.c_str());
                auto cp_cmd = "cp " + tmpFile + " " + transitFile;
                (void)system(cp_cmd.c_str());
            });
    When(Method(mock, deleteContent))
        .AlwaysDo(
            [&targetFile](const rsi::Filename& transitFile) {
                std::ifstream inHex(transitFile);
                REQUIRE(inHex.good());
                std::ofstream outBin(targetFile);
                REQUIRE(outBin.good());
                rsi::ConvertFile converter;
                converter.convertToBin(inHex, outBin);
            });

    rsi::VendorInterface& i = mock.get();
    i.addContent(transitFile);
    i.changeContent(transitFile);
    i.deleteContent(transitFile);
    Verify(Method(mock, addContent));
    Verify(Method(mock, changeContent));
    Verify(Method(mock, deleteContent));
}
