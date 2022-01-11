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

#include <extras_rsi/remote/monitors/File.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <iostream>
#include <sstream>
#include <filesystem>

#include "../../unittesting/catch.hpp"
#include "../../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Test File Monitor", "[CausalityInterface]") {

    SystemException::assertion("rm -rf testit; mkdir testit; ", __INFO__);
    SystemException::assertion("cp data/exparx.webflow.zip testit; ", __INFO__);
    SystemException::assertion("cp data/src.zip testit; ", __INFO__);

    Pathname pathname = "testit/exparx.webflow.zip";
    rsi::FileMonitor monitor(pathname);
    rsi::CausalityInterface& i = monitor;

    REQUIRE(fs::exists(pathname));
    i.cause();
    REQUIRE(!fs::exists(pathname));
    i.cause();
    REQUIRE(!fs::exists(pathname));

    SystemException::assertion("rm -rf testit;rm -rf testit2;rm -rf runtime;", __INFO__);

}
