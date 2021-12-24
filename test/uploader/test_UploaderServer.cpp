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

#include <extras_rsi/uploader/Uploader.hpp>
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
 * @brief Test UploaderInterface: uploader_server
 *
 *
 */
SCENARIO("Test UploaderInterface: uploader_server", "[UploaderInterface]") {

    //
    // setup uploader_server
    // 
    killAllServers();
    SystemException::assertion("rm -rf testit2; mkdir testit2; ", __INFO__);
    REQUIRE(!fs::exists("testit2/exparx.webflow.zip"));
    SystemException::assertion("build/uploader_server 127.0.0.1 8080 testit2/exparx.webflow.zip &", __INFO__);
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(2));

    //
    // setup uploader_client
    //
    SystemException::assertion("rm -rf testit; mkdir testit; ", __INFO__);
    SystemException::assertion("cp data/exparx.webflow.zip testit; ", __INFO__);
    REQUIRE(fs::exists("testit/exparx.webflow.zip"));

    const char* argv[] = { "build/uploader_client", "127.0.0.1", "8080", "testit/exparx.webflow.zip" };
    int argc = sizeof(argv) / sizeof(argv[0]);

    std::cout << extras::start(argv[0]) << std::endl;
    extras::rsi::UploaderClient uploader;
    uploader.parameters(argc, argv);
    uploader.connect();
    uploader.transfer();
    std::cout << extras::pass("File data uploaded successfully") << std::endl;
    uploader.close();
    std::cout << extras::end(argv[0]) << std::endl << std::endl;

    REQUIRE(fs::exists("testit/exparx.webflow.zip"));
    REQUIRE(fs::exists("testit2/exparx.webflow.zip"));

    //
    // cleanup
    //
    killAllServers();
    SystemException::assertion("rm -rf testit", __INFO__);

}

