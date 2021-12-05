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

#include <extras_rsi/uploader/Parameters.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ParametersInterface: uploader parameters", "[UploaderParameters]") {

    // define the parameters 
    const char* argv[] = {
         "build/uploader_client", "data/exparx.webflow.zip", "137.184.218.130", "8080" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    Parameters _parameters;

    // define the mock 
    Mock<rsi::uploader::ParametersInterface> mock;
    When(Method(mock, parameters))
        .AlwaysDo(
            [&_parameters](int argc, char const* argv[]) {
                rsi::Parameters result;
                for (int i = 0; i < argc; i++) {
                    auto arg = argv[i];
                    result.push_back(arg);
                }
                _parameters = result;
                return _parameters;
            });

    // define the instance 
    rsi::uploader::ParametersInterface& i = mock.get();

    // test the expected results
    REQUIRE(i.parameters(argc, argv) == _parameters);
    When(Method(mock, program)).AlwaysReturn(_parameters[0]);
    When(Method(mock, ip)).AlwaysReturn(_parameters[1]);
    When(Method(mock, port)).AlwaysReturn(_parameters[2]);
    When(Method(mock, filename)).AlwaysReturn(_parameters[3]);
    REQUIRE(i.program() == _parameters[0]);
    REQUIRE(i.ip() == _parameters[1]);
    REQUIRE(i.port() == _parameters[2]);
    REQUIRE(i.filename() == _parameters[3]);
    Verify(Method(mock, parameters));
    Verify(Method(mock, program));
    Verify(Method(mock, ip));
    Verify(Method(mock, port));
    Verify(Method(mock, filename));
}
