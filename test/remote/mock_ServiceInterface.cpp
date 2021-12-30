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

#include <extras_rsi/remote/ServiceInterface.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock RemoteServiceInterface", "[RemoteServiceInterface]") {

    const char* argv[] = {
        "build/rsi",
        "137.184.218.130:8080",
        "data/src.zip",
        "data/exparx.webflow.zip"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    // output parameters
    rsi::ServiceTypeList request_list = {
        "upload 137.184.218.130 9000 data/src.zip",
        "upload 137.184.218.130 9001 data/exparx.webflow.zip",
        "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip",
        "download 137.184.218.130 9003 data/src.zip"
    };

    rsi::ParameterList _parameterList;

    Mock<rsi::RemoteServiceInterface> mock;
    When(Method(mock, parameters))
        .AlwaysDo(
            [&_parameterList](int argc, char const* argv[]) {
                rsi::NotEnoughParametersException::assertion(argc, 3, __INFO__);
                for (auto i = 1; i < argc; i++)
                    _parameterList.push_back(argv[i]);
            });

    rsi::RemoteServiceInterface& i = mock.get();

    REQUIRE(_parameterList.size() == 0);
    i.parameters(argc, argv);
    REQUIRE(_parameterList.size() == 3);

    Verify(Method(mock, parameters));
}
