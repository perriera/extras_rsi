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

#include <extras_rsi/prototype/socketpool/SocketPool.hpp>
#include <extras_rsi/prototype/requests/RequestType.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Test sockets::ParametersInterface", "[sockets::ParametersInterface]") {

    const char* argv[] = {
        "build/socketpool_client",
        "137.184.218.130",
        "8080",
        "data/src.zip",
        "data/exparx.webflow.zip"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    rsi::Parameters _parameters;
    rsi::Parameter _program;
    rsi::Parameter _ip;
    rsi::Parameter _port;
    rsi::Parameter _filename;
    rsi::SocketRequestTypeList _requests;
    _requests.push_back(argv[4]);

    rsi::SocketParaneters socketParameters;

    rsi::sockets::ParametersInterface& i = socketParameters;
    i.parameters(argc, argv);
    REQUIRE(i.program() == argv[0]);
    REQUIRE(i.ip() == argv[1]);
    REQUIRE(i.port() == argv[2]);
    REQUIRE(i.filename() == argv[3]);
    REQUIRE(i.requests() == _requests);

}
