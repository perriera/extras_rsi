#include <rsi/parcel/Wrap.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <rsi/exceptions.hpp>
#include <ng_imploder/imploder/Imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Mock WrapInterface: Imploder", "[WrapInterface]") {

    rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    rsi::Parameter imploded = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip");
    rsi::Parameter exploded = extras::replace_all(original, "webflow.zip", "webflow.zip_exploded.zip");
    Mock<rsi::WrapInterface> mock;

    When(Method(mock, wrap))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                ng::Imploder imploder(filename);
                imploder.implode();
                return imploder.imploded();
            });

    When(Method(mock, unWrap))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                ng::Imploder imploder(filename);
                imploder.explode();
                return imploder.exploded();
            });

    rsi::WrapInterface& i = mock.get();

    ng::Imploder imploder(original);
    imploder.clean();

    REQUIRE(fs::exists(imploder.original()));
    REQUIRE(!fs::exists(imploder.imploded()));
    REQUIRE(!fs::exists(imploder.exploded()));
    cout << "HELLO JESUS" << endl;
    cout << original << endl;
    cout << imploded << endl;
    cout << "HELLO JESUS" << endl;
    auto result = i.wrap(original);
    cout << result << endl;
    cout << "HELLO JESUS" << endl;
    REQUIRE(result == imploded);
    REQUIRE(fs::exists(imploder.original()));
    REQUIRE(fs::exists(imploder.imploded()));
    REQUIRE(!fs::exists(imploder.exploded()));
    REQUIRE(i.unWrap(original) == exploded);
    REQUIRE(fs::exists(imploder.original()));
    REQUIRE(fs::exists(imploder.imploded()));
    REQUIRE(fs::exists(imploder.exploded()));
    imploder.clean();
    REQUIRE(fs::exists(imploder.original()));
    REQUIRE(!fs::exists(imploder.imploded()));
    REQUIRE(!fs::exists(imploder.exploded()));
    Verify(Method(mock, wrap));
    Verify(Method(mock, unWrap));

}
