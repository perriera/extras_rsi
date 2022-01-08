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

#include <extras_rsi/prototype/requests/RequestTypeTwo.hpp>
#include <extras_rsi/prototype/socketpool/Parameters.hpp>
#include <extras_rsi/prototype/socketpool/Client.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"

using namespace extras;
using namespace std;

SCENARIO("Test RequestTypeCompilerInterface: TypeTwo", "[RequestTypeCompilerInterface]") {

    rsi::SocketParaneters parameters;
    rsi::PortAuthority portAuthority;
    const char* argv[] = {
        "/home/perry/Projects/extras_rsi/build/socketpool_client",
        "137.184.218.130",
        "8080",
        "data/exparx.webflow.zip",
        "upload",
        "data/exparx.webflow.zip",
        "upload",
        "data/src.zip",
        "vendor",
        "download",
        "data/exparx.freeformjs.zip",
    };

    int argc = sizeof(argv) / sizeof(argv[0]);
    parameters.parameters(argc, argv);
    std::string msg = parameters;
    extras::rsi::ServiceTypeCompilerVendor vendor;
    rsi::SocketPoolClient client(msg, vendor);
    int socket = std::stoi(client.port());

    //
    rsi::RequestTypeCompilerTypeTwo typeII(vendor, socket);
    //     REQUIRE

    rsi::RequestTypeCompilerInterface& i = typeII;
    auto _compilation = i.compile(parameters, portAuthority);
    if (socket != 8080) // included for consistency
        _compilation.send_line_block("");
    auto cmds = vendor.clients(_compilation.compilation());
    REQUIRE(cmds.size() == 4);

    std::vector<std::string> testData = {
        "build/uploader_client 137.184.218.130 9000 data/exparx.webflow.zip ",
        "build/uploader_client 137.184.218.130 9001 data/src.zip ",
        "build/vendor_client 137.184.218.130 9002 ",
        "build/downloader_client 137.184.218.130 9003 data/exparx.freeformjs.zip "
    };
    REQUIRE(cmds[0] == testData[0]);
    REQUIRE(cmds[1] == testData[1]);
    REQUIRE(cmds[2] == testData[2]);
    REQUIRE(cmds[3] == testData[3]);
    for (auto cmd : cmds) {
        std::cout << "msg received: " << cmd << std::endl;
    }


}
