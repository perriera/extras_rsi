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
#include <extras_rsi/service/Uploader.hpp>
#include <iostream>

#include "../../unittesting/catch.hpp"
#include "../../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Dock uploader::ParametersInterface", "[uploader::ParametersInterface]") {

    const char* argv[] = {
         "build/uploader_client",
         "137.184.218.130",
         "8080",
         "data/src.zip",
         "data/exparx.webflow.zip"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);
    Parameters _parameters;
    Parameters _extra;

    // define the mock 
    Mock<rsi::uploader::ParametersInterface> mock;
    When(Method(mock, parameters))
        .AlwaysDo(
            [&_parameters, &_extra](int argc, char const* argv[]) {
                // if (argc == 2 && rsi::Parameter(argv[1]) == "-help")
                // help();
                if (argc < 4) {
                    std::cout << "parameters: <ip> <port> <filename>  | -help " << std::endl;
                    throw rsi::RSIException("parameters: <ip> <port> <filename> ", __INFO__);
                }
                rsi::Parameters result;
                for (int i = 0; i < argc; i++) result.push_back(argv[i]);
                _parameters = result;
                for (int i = 4; i < argc; i++) _extra.push_back(argv[i]);
                return _parameters;
            });
    When(Method(mock, program))
        .AlwaysDo(
            [&_parameters]() {
                return _parameters[0];
            });
    When(Method(mock, ip))
        .AlwaysDo(
            [&_parameters]() {
                return _parameters[1];
            });
    When(Method(mock, port))
        .AlwaysDo(
            [&_parameters]() {
                return _parameters[2];
            });
    When(Method(mock, filename))
        .AlwaysDo(
            [&_parameters]() {
                return _parameters[3];
            });
    When(Method(mock, extra_files))
        .AlwaysDo(
            [&_extra]() {
                return _extra;
            });

    // define the instance 
    rsi::uploader::ParametersInterface& i = mock.get();

    // test the expected results
    REQUIRE(i.parameters(argc, argv) == _parameters);
    REQUIRE(i.program() == _parameters[0]);
    REQUIRE(i.ip() == _parameters[1]);
    REQUIRE(i.port() == _parameters[2]);
    REQUIRE(i.filename() == _parameters[3]);
    REQUIRE(i.extra_files() == _extra);

    Verify(Method(mock, parameters));
    Verify(Method(mock, program));
    Verify(Method(mock, ip));
    Verify(Method(mock, port));
    Verify(Method(mock, filename));
    Verify(Method(mock, extra_files));

    SystemException::assertion("rm -rf testit;rm -rf testit2;rm -rf runtime;", __INFO__);

}
