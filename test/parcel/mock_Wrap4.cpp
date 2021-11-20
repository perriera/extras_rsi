#include <rsi/parcel/Wrap.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/parcel/ParcelImploder.hpp>
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

SCENARIO("Mock WrapInterface: ParcelImploder", "[WrapInterface]") {

    rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    rsi::Parameter wrapped = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip_packed.txt");
    rsi::Parameter duplicate = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip_duplicate.bin");
    Mock<rsi::WrapInterface> mock;

    When(Method(mock, wrap))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                ng::Imploder imploder(filename);
                imploder.implode();
                rsi::Parcel parcel(imploder.imploded());
                parcel.pack();
                auto x = parcel.packed();
                return x;
            });

    When(Method(mock, unWrap))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                ng::Imploder imploder(filename);
                auto z1 = imploder.imploded();
                rsi::Parcel parcel(z1);
                auto z2 = parcel.packed();
                parcel.unpack();
                auto x = parcel.duplicate();
                return x;
            });

    When(Method(mock, clean))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                ng::Imploder imploder(filename);
                auto z1 = imploder.imploded();
                rsi::Parcel parcel(z1);
                auto z2 = parcel.packed();
                parcel.clean();
                imploder.clean();
                auto x = filename;
                return x;
            });

    rsi::WrapInterface& i = mock.get();

    REQUIRE(fs::exists(original));
    REQUIRE(i.wrap(original) == wrapped);
    REQUIRE(i.unWrap(original) == duplicate);
    REQUIRE(i.clean(original) == original);
    REQUIRE(fs::exists(original));
    Verify(Method(mock, wrap));
    Verify(Method(mock, unWrap));
    Verify(Method(mock, clean));

}
