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

#include <extras_rsi/remote/InvokableInterface.hpp>
#include <extras_rsi/prototype/socketpool/SocketPool.hpp>
#include <extras_rsi/remote/Service.hpp>
#include <extras_rsi/remote/ParametersX.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <sstream>
#include <extras/devices/ansi_colors.hpp>
#include <extras/status/StatusLine.hpp>
#include <filesystem>
#include <chrono>
#include <thread>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace std;
using namespace fakeit;
namespace fs = std::filesystem;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

void killAllServers();

/**
 * @brief Test SocketPoolInterface: socketpool_server
 *
 */
SCENARIO("Test InvokableInterface: client/server", "[InvokableInterface]") {

    //
    // setup rsi_server
    //
    killAllServers();
    SystemException::assertion("build/rsi_server 127.0.0.1:8080 9000-9500 &", __INFO__);
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(2));

    //
    // setup rsi_client
    //
    SystemException::assertion("rm -rf testit; mkdir testit; ", __INFO__);
    SystemException::assertion("cp data/src.zip testit/; cp data/exparx.webflow.zip testit; ", __INFO__);
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/exparx.webflow.zip"));

    SystemException::assertion("build/rsi_client 127.0.0.1:8080 testit/src.zip testit/exparx.webflow.zip", __INFO__);

    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/exparx.webflow.zip"));

    //
    // cleanup
    //
    killAllServers();
    REQUIRE_THROWS_AS(rsi::SocketPool::killServers("rsi_server"), extras::rsi::NoServersToKillException);
    SystemException::assertion("rm -rf testit;rm -rf testit2;rm -rf runtime;", __INFO__);
}

