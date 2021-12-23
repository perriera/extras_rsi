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

#include <extras_rsi/vendor/Vendor.hpp>
#include <extras_rsi/socketpool/SocketPool.hpp>
#include <extras/strings.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <extras_rsi/socketpool/Client.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>
#include <extras_rsi/exceptions.hpp>
#include <chrono>
#include <thread>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;
namespace fs = std::filesystem;

void killServers(std::string pattern);
void killAllServers();

/**
 * @brief Test SocketPoolInterface: socketpool_server
 *
 * @note AT THE MOMENT THIS TEST IS FLAWED
 *       AS IT HAS BEEN REVEALED THAT ON A LOCAL SERVER
 *       BOTH THE CLIENT AND THE SERVER ARE ACTING ON THE
 *       SAME DIRECTORY. (ideally, this is not the way
 *       the way it should work, however it does show
 *       that the semaphore logic is working properly).
 *
 */
SCENARIO("Test UploaderInterface: vendor_client", "[UploaderInterface]") {

    //
    // setup socketpool_server
    // 
    killAllServers();
    SystemException::assertion("rm -rf testit2; mkdir testit2; ", __INFO__);
    SystemException::assertion("cp data/src.zip testit2; cp data/exparx.webflow.zip testit2; ", __INFO__);
    REQUIRE(fs::exists("testit2/src.zip"));
    REQUIRE(fs::exists("testit2/exparx.webflow.zip"));
    SystemException::assertion("build/vendor_server 127.0.0.1 8080 testit2/exparx.webflow.zip &", __INFO__);
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(2));

    //
    // setup socketpool_client
    //
    SystemException::assertion("rm -rf testit; mkdir testit; ", __INFO__);
    SystemException::assertion("cp data/src.zip testit; cp data/exparx.webflow.zip testit; ", __INFO__);
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/exparx.webflow.zip"));

    SystemException::assertion("build/vendor_client 127.0.0.1 8080 testit/src.zip testit/exparx.webflow.zip", __INFO__);

    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/exparx.webflow.zip"));
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(2));
    REQUIRE(fs::exists("testit2/src.zip"));
    REQUIRE(fs::exists("testit2/exparx.webflow.zip"));

    //
    // cleanup
    //
    killAllServers();
    SystemException::assertion("rm -rf testit", __INFO__);

}

