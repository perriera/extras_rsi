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

#include <extras_rsi/remote/monitors/NgMonitor.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <extras_arc/zipper.hpp>

#include "../../unittesting/catch.hpp"
#include "../../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Test NgMonitor", "[CausalityInterface]") {

    SystemException::assertion("rm -rf testit; mkdir testit; ", __INFO__);
    SystemException::assertion("cp data/exparx.webflow.zip testit; ", __INFO__);
    SystemException::assertion("cp data/src.zip testit; ", __INFO__);

    Filename webflow = "testit/exparx.webflow.zip";
    Filename zipFile = "testit/src.zip";
    Pathname srcDir = "testit/";

    arc::Zipper zipper(zipFile, srcDir);

    // test unzip
    REQUIRE(fs::exists("testit/src.zip"));
    zipper.unzip();
    SystemException::assertion("rm testit/src.zip", __INFO__);
    REQUIRE(!fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/src"));
    REQUIRE(fs::exists("testit/src/app/app.component.ts"));
    zipper.create();
    REQUIRE(fs::exists("testit/src.zip"));
    zipper.create();
    REQUIRE(fs::exists("testit/src.zip"));

    rsi::NgMonitor monitor(webflow, srcDir);
    rsi::CausalityInterface& i = monitor;

    REQUIRE(fs::exists(webflow));
    i.cause();
    REQUIRE(!fs::exists(webflow));
    i.cause();
    REQUIRE(!fs::exists(webflow));

    SystemException::assertion("rm -rf testit;rm -rf testit2;rm -rf runtime;", __INFO__);

}
