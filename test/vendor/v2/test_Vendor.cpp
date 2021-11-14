// #include <rsi/vendor/v2/Vendor.hpp>
// #include <extras/strings.hpp>
// #include <extras/filesystem/paths.hpp>
// #include <filesystem>
// #include <iostream>

// #include "../../unittesting/catch.hpp"
// #include "../../unittesting/fakeit.hpp"

// using namespace extras;
// namespace fs = std::filesystem;

// SCENARIO("Test VendorInterface (v2)", "[VendorInterface]") {

//     rsi::Parameter parcel = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");
//     const char* argv[] = {
//         "socketclient", parcel.c_str(),  "127.0.0.1", "8080",
//         "vendor",   "download" };
//     int argc = 6;

//     rsi::VendorClient testUnit;
//     testUnit.parameters(argc, argv);
//     rsi::VendorInterface& i = testUnit;

//     // // wrap parcel
//     // if (fs::exists(testUnit.parcel()))
//     //     fs::remove(testUnit.parcel());
//     // REQUIRE(!fs::exists(testUnit.parcel()));
//     // REQUIRE(fs::exists(testUnit.payload()));
//     // i.wrapParcel();
//     // REQUIRE(fs::exists(testUnit.parcel()));

//     // // deliver parcel
//     // REQUIRE(fs::exists(testUnit.parcel()));
//     // fs::remove(testUnit.payload());
//     // REQUIRE(!fs::exists(testUnit.payload()));
//     // i.deliverParcel();
//     // REQUIRE(fs::exists(testUnit.payload()));
//     // fs::remove(testUnit.payload());
//     // REQUIRE(!fs::exists(testUnit.payload()));

//     // // un parcel
//     // i.unwrapParcel();
//     // REQUIRE(fs::exists(testUnit.payload()));
// }
