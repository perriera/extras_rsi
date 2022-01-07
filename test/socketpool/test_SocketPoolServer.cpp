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

 // build/uploader_client data/cplusplusorg.freeformjs.imploded.zip 137.184.218.130 9003
 // build/uploader_server send.txt 137.184.218.130 9003

 // build/uploader_client data/cplusplusorg.freeformjs.imploded.zip 137.184.218.130 9003
 // build/uploader_server send.txt 137.184.218.130 9003

 // build/_deps/extras_rsi-build/socketpool_server 127.0.0.1 8080 send.txt  
 // build/_deps/extras_rsi-build/socketpool_client 127.0.0.1 8080 data/cplusplusorg.freeformjs.imploded.zip upload vendor download

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
SCENARIO("Test SocketPoolInterface: socketpool_server", "[SocketPoolInterface]") {

    //
    // setup socketpool_server
    //
    killAllServers();
    SystemException::assertion("rm -rf testit; mkdir testit; ", __INFO__);
    SystemException::assertion("build/socketpool_server 127.0.0.1 8088 8000-8500 &", __INFO__);
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(2));

    //
    // setup socketpool_client
    //
    SystemException::assertion("cp data/src.zip testit/; cp data/exparx.webflow.zip testit; ", __INFO__);
    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/exparx.webflow.zip"));

    const char* argv[] = { "build/socketpool_client", "127.0.0.1", "8088", "testit/src.zip", "testit/exparx.webflow.zip" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    std::cout << extras::start(argv[0]) << std::endl;
    extras::rsi::ServiceTypeCompilerVendor vendor;
    extras::rsi::SocketPoolClient client(vendor);
    client.parameters(argc, argv);
    client.connect();
    client.transfer();
    std::cout << extras::pass("File sockets allocated successfully") << std::endl;
    client.close();
    std::cout << extras::end(argv[0]) << std::endl << std::endl;

    REQUIRE(fs::exists("testit/src.zip"));
    REQUIRE(fs::exists("testit/exparx.webflow.zip"));

    //
    // cleanup
    //
    killAllServers();
    SystemException::assertion("rm -rf testit", __INFO__);

}

