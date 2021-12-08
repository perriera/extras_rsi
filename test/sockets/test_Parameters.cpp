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

#include <extras_rsi/sockets/Parameters.hpp>
#include <extras_rsi/socketpool/Client.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"

using namespace extras;

SCENARIO("Test ParametersInterface: basic upload/vendor/download", "[SocketPoolParameters]") {

    // define the parameters 
    const char* argv[] = {
         "build/uploader_client", "data/exparx.webflow.zip", "137.184.218.130", "8080" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    Parameters _parameters;
    for (int i = 0; i < argc; i++) {
        auto arg = argv[i];
        _parameters.push_back(arg);
    }

    // define the mock 
    extras::rsi::ServiceTypeCompilerVendor vendor;
    extras::rsi::SocketPoolClient client(vendor);

    // define the instance 
    rsi::sockets::ParametersInterface& i = client;

    // test the expected results
    REQUIRE(i.parameters(argc, argv) == _parameters);
    // REQUIRE(i.program() == _parameters[0]);
    // REQUIRE(i.ip() == _parameters[1]);
    // REQUIRE(i.port() == _parameters[2]);
}
