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

using namespace extras;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Test WrapInterface: ParcelImploder", "[WrapInterface]") {

    rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    rsi::Parameter wrapped = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip_packed.txt");
    rsi::Parameter duplicate = extras::replace_all(original, "webflow.zip", "webflow.zip_exploded.zip");

    rsi::ParcelImploder parcelImploder;
    rsi::WrapInterface& i = parcelImploder;

    i.clean(original);

    REQUIRE(fs::exists(original));
    REQUIRE(i.wrap(original) == wrapped);
    REQUIRE(i.unWrap(original) == duplicate);
    REQUIRE(i.merge(original) == original);
    REQUIRE(i.clean(original) == original);
    REQUIRE(fs::exists(original));

}
