/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

#include <extras_arc/wrap.hpp>
#include <extras_arc/imploder.hpp>
#include <extras_arc/parcel.hpp>
#include <extras_arc/parcel.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <extras_arc/imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>


#include "../unittesting/catch.hpp"

using namespace extras;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Test WrapInterface: ParcelImploder", "[BadCRC]") {

    auto cpCmd = "cp data/badcrc/src.zip data/badcrc/badcrc.zip";
    SystemException::assertion(cpCmd, __INFO__);

    Parameter testdata = ~extras::Paths("data/badcrc/badcrc.zip");

    arc::ParcelImploder parcelImploder(testdata);
    arc::WrapInterface& i = parcelImploder;

    //
    // Scenario 1: Original exists
    //

    REQUIRE(i.clean() == testdata);
    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

    auto a = i.wrap();
    auto b = i.wrapped();

    REQUIRE(i.wrap() == i.wrapped());
    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(fs::exists(i.wrapped()));

    REQUIRE(i.unWrap() == i.unWrapped());
    REQUIRE(fs::exists(testdata));
    REQUIRE(fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

    REQUIRE(i.merge() == testdata);
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(fs::exists(testdata));

    REQUIRE(i.clean() == testdata);
    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

    //
    // Scenario 2: Original does not exist
    //

    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

    REQUIRE(i.wrap() == i.wrapped());
    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(fs::exists(i.wrapped()));

    REQUIRE(fs::exists(testdata));
    REQUIRE(fs::exists(i.wrapped()));
    auto rmCmd = "rm data/exparx.webflow.zip";
    SystemException::assertion(rmCmd, __INFO__);
    REQUIRE(!fs::exists(testdata));
    REQUIRE(fs::exists(i.wrapped()));

    REQUIRE(i.unWrap() == i.unWrapped());
    REQUIRE(!fs::exists(testdata));
    REQUIRE(fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

    REQUIRE(i.merge() == testdata);
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(fs::exists(testdata));

    REQUIRE(i.clean() == testdata);
    REQUIRE(fs::exists(testdata));
    REQUIRE(!fs::exists(i.unWrapped()));
    REQUIRE(!fs::exists(i.wrapped()));

}
