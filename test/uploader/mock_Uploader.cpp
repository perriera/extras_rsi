#include <rsi/uploader/Uploader.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/system.hpp>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock UploaderInterface: basic", "[UploaderInterface]") {

    rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    rsi::Parameter _program = "uploader_client";
    rsi::Parameter _filename = original;
    rsi::Parameter _ip = "127.0.0.1";
    rsi::Parameter _port = "8080";

    Mock<rsi::UploaderInterface> mock;
    const char* argv[] = { _program.c_str(), _ip.c_str(), _port.c_str(),
                            _filename.c_str(),   "upload",  "vendor", "download" };
    int argc = 7;

    When(Method(mock, program)).Return(_program);
    When(Method(mock, filename)).Return(_filename);
    When(Method(mock, ip)).Return(_ip);
    When(Method(mock, port)).Return(_port);
    When(Method(mock, parameters))
        .AlwaysDo(
            [](int argc, char const* argv[]) {
                return rsi::Parameters();
            });

    When(Method(mock, connect))
        .AlwaysDo(
            []() {
            });

    When(Method(mock, transfer))
        .AlwaysDo(
            []() {
            });

    When(Method(mock, close))
        .AlwaysDo(
            []() {
            });

    rsi::UploaderInterface& i = mock.get();

    REQUIRE(fs::exists(original));
    REQUIRE(i.parameters(argc, argv) == rsi::Parameters());
    REQUIRE(i.program() == _program);
    REQUIRE(i.filename() == _filename);
    REQUIRE(i.ip() == _ip);
    REQUIRE(i.port() == _port);
    REQUIRE(fs::exists(original));
    Verify(Method(mock, parameters));
    Verify(Method(mock, program));
    Verify(Method(mock, filename));
    Verify(Method(mock, ip));
    Verify(Method(mock, port));
}
