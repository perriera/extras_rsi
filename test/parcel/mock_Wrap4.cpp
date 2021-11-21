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
#include <extras/filesystem/system.hpp>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Mock WrapInterface: ParcelImploder", "[WrapInterface]") {

    rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    rsi::Parameter wrapped = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip_packed.txt");
    rsi::Parameter duplicate = extras::replace_all(original, "webflow.zip", "webflow.zip_exploded.zip");
    Mock<rsi::WrapInterface> mock;

    When(Method(mock, wrap))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                ng::Imploder imploder(filename);
                imploder.implode();
                rsi::Parcel parcel(imploder.imploded());
                parcel.pack();
                return parcel.packed();
            });

    When(Method(mock, unWrap))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                ng::Imploder imploder(filename);
                rsi::Parcel parcel(imploder.imploded());
                parcel.unpack();
                parcel.merge();
                parcel.clean();
                imploder.explode();
                return imploder.exploded();
            });

    When(Method(mock, merge))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                ng::Imploder imploder(filename);
                imploder.merge();
                imploder.clean();
                return filename;
            });
    When(Method(mock, clean))
        .AlwaysDo(
            [](const rsi::Filename& filename) {
                ng::Imploder imploder(filename);
                rsi::Parcel parcel(imploder.imploded());
                parcel.clean();
                imploder.clean();
                return filename;
            });

    rsi::WrapInterface& i = mock.get();

    i.clean(original);

    REQUIRE(fs::exists(original));
    REQUIRE(i.wrap(original) == wrapped);
    REQUIRE(i.unWrap(original) == duplicate);
    REQUIRE(i.merge(original) == original);
    REQUIRE(i.clean(original) == original);
    REQUIRE(fs::exists(original));
    Verify(Method(mock, wrap));
    Verify(Method(mock, unWrap));
    Verify(Method(mock, clean));

}
