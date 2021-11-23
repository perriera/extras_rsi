#include <rsi/parcel/Wrap.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/parcel/Wrap.hpp>
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

    rsi::Parameter testdata = ~extras::Paths("data/exparx.webflow.zip");

    SystemException::assertion("rm -rf data/client", __INFO__);
    SystemException::assertion("rm -rf data/server", __INFO__);
    SystemException::assertion("mkdir data/client", __INFO__);
    SystemException::assertion("mkdir data/server", __INFO__);
    auto copydata = "cp " + testdata + " " + "data/client";
    SystemException::assertion(copydata, __INFO__);

    rsi::Parameter original = extras::replace_all(testdata, "data/", "data/client/");
    rsi::Parameter wrapped = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip_packed.txt");
    rsi::Parameter unwrapped = extras::replace_all(original, "webflow.zip", "webflow.zip_imploded.zip");
    rsi::Parameter duplicate = extras::replace_all(original, "webflow.zip", "webflow.zip_exploded.zip");
    rsi::Parameter wrapped_onServer;
    rsi::Parameter filename_onServer;

    rsi::ParcelImploder parcelImploder;
    rsi::WrapInterface& i = parcelImploder;

    i.clean(original);

    REQUIRE(fs::exists(original));
    REQUIRE(i.wrap(original) == wrapped);
    {
        auto copydata = "cp " + wrapped + " " + "data/server";
        SystemException::assertion(copydata, __INFO__);
        wrapped_onServer = extras::replace_all(wrapped, "data/client", "data/server");
        filename_onServer = extras::replace_all(original, "data/client", "data/server");
        unwrapped = extras::replace_all(unwrapped, "data/client", "data/server");
    }

    REQUIRE(i.unWrap(filename_onServer) == unwrapped);
    REQUIRE(fs::exists(unwrapped));
    REQUIRE(i.merge(filename_onServer) == filename_onServer);
    REQUIRE(!fs::exists(unwrapped));
    REQUIRE(fs::exists(filename_onServer));
    REQUIRE(i.clean(filename_onServer) == filename_onServer);
    REQUIRE(fs::exists(filename_onServer));
    REQUIRE(fs::exists(original));

}
