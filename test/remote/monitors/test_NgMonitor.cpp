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
#include <extras_rsi/prototype/socketpool/SocketPool.hpp>
#include <extras_rsi/remote/Service.hpp>
#include <extras_arc/zipper.hpp>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <thread>

#include "../../unittesting/catch.hpp"
#include "../../unittesting/fakeit.hpp"

using namespace extras;
using namespace std;
using namespace fakeit;
namespace fs = std::filesystem;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

void killAllServers();


SCENARIO("Test NgMonitor", "[NgMonitor]") {

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
    SystemException::assertion("rm testit/src.zip", __INFO__);
    REQUIRE(!fs::exists("testit/src.zip"));

    //
    // setup rsi_server
    //
    killAllServers();
    SystemException::assertion("build/rsi_server 127.0.0.1:8080 9000-9500 &", __INFO__);
    sleep_for(nanoseconds(10));

    const char* argv[] = {
        "build/rsi",
        "127.0.0.1:8080",
        webflow.c_str(),
        srcDir.c_str()
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    rsi::NgMonitor monitor;
    rsi::CausalityInterface& i = monitor;

    monitor.parse(argc, argv);

    REQUIRE(fs::exists("testit/src/app/app.component.ts"));
    fs::remove("testit/src/app/app.component.ts");
    REQUIRE(!fs::exists("testit/src/app/app.component.ts"));

    REQUIRE(fs::exists(webflow));
    i.cause();
    REQUIRE(!fs::exists(webflow));
    i.cause();
    REQUIRE(!fs::exists(webflow));

    REQUIRE(!fs::exists("testit/src.zip"));
    REQUIRE(!fs::exists("testit/exparx.webflow.zip"));
    REQUIRE(fs::exists("testit/src"));

    REQUIRE(!fs::exists("testit/src/app/app.component.ts"));

    //
    // cleanup
    //
    killAllServers();
    REQUIRE_THROWS_AS(rsi::SocketPool::killServers("rsi_server"), extras::rsi::NoServersToKillException);
    SystemException::assertion("rm -rf testit;rm -rf testit2;rm -rf runtime;", __INFO__);

}
