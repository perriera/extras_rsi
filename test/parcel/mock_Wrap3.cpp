#include <rsi/parcel/Wrap.hpp>
#include <extras/filesystem/paths.hpp>
#include <filesystem>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock WrapInterface: Parcel", "[WrapInterface]") {

    rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    rsi::Parameter packed = extras::replace_all(original, "webflow.zip", "webflow.zip_packed.txt");
    rsi::Parameter unpacked = extras::replace_all(original, "webflow.zip", "webflow.zip_duplicate.bin");
    Mock<rsi::WrapInterface> mock;

    When(Method(mock, wrap))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                rsi::Parcel parcel(filename);
                parcel.pack();
                auto x = parcel.packed();
                return x;
            });

    When(Method(mock, unWrap))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                rsi::Parcel parcel(filename);
                parcel.unpack();
                auto y = parcel.duplicate();
                return y;
            });

    rsi::WrapInterface& i = mock.get();

    rsi::Parcel parcel(original);
    parcel.clean();

    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(!fs::exists(parcel.packed()));
    REQUIRE(!fs::exists(parcel.duplicate()));
    REQUIRE(i.wrap(original) == packed);
    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(fs::exists(parcel.packed()));
    REQUIRE(!fs::exists(parcel.duplicate()));
    REQUIRE(i.unWrap(original) == unpacked);
    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(fs::exists(parcel.packed()));
    REQUIRE(fs::exists(parcel.duplicate()));
    parcel.clean();
    REQUIRE(fs::exists(parcel.original()));
    REQUIRE(!fs::exists(parcel.packed()));
    REQUIRE(!fs::exists(parcel.duplicate()));
    Verify(Method(mock, wrap));
    Verify(Method(mock, unWrap));

}
