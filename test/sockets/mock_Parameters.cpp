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
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ParametersInterface: basic upload/vendor/download", "[SocketPoolParameters]") {

    const char* argv[] = {
        "build/socketpool_client", "137.184.218.130", "8080",
        "data/exparx.webflow.zip", "upload", "vendor", "download"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);
    Parameters _parameters;
    rsi::SocketRequestTypeList _requests;

    Mock<rsi::sockets::ParametersInterface> mock;
    When(Method(mock, parameters))
        .AlwaysDo(
            [&_parameters, &_requests](int argc, char const* argv[]) {
                _parameters.clear();
                for (int i = 0; i < 3; i++) {
                    auto arg = argv[i];
                    _parameters.push_back(arg);
                }
                for (int i = 3; i < argc; i++) {
                    rsi::RequestType arg = argv[i];
                    _requests.push_back(arg);
                }

                return _parameters;
            });

    rsi::sockets::ParametersInterface& i = mock.get();
    REQUIRE(i.parameters(argc, argv) == _parameters);
    Verify(Method(mock, parameters));
}
