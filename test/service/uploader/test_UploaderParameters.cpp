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

#include <extras_rsi/service/Parameters.hpp>
#include <extras_rsi/service/uploader/Client.hpp>
#include <extras_rsi/service/uploader/Server.hpp>
#include <iostream>

#include "../../unittesting/catch.hpp"
#include "../../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Test uploader::ParametersInterface", "[uploader::ParametersInterface]") {

    const char* argv[] = {
         "build/uploader_client",
         "137.184.218.130",
         "8080",
         "data/src.zip",
         "data/exparx.webflow.zip"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);
    Parameters _parameters = { argv[0], argv[1], argv[2], argv[3], argv[4] };
    Parameters _extra = { argv[4] };

    rsi::UploaderClient client;
    // define the instance 
    rsi::uploader::ParametersInterface& i = client;

    // test the expected results
    REQUIRE(i.parameters(argc, argv) == _parameters);
    REQUIRE(i.program() == _parameters[0]);
    REQUIRE(i.ip() == _parameters[1]);
    REQUIRE(i.port() == _parameters[2]);
    REQUIRE(i.filename() == _parameters[3]);
    REQUIRE(i.extra_files() == _extra);

    SystemException::assertion("rm -rf testit;rm -rf testit2;rm -rf runtime;", __INFO__);

}
