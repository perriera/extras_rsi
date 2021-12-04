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

    const char* argv[] = {
         "build/uploader_client", "data/exparx.webflow.zip", "137.184.218.130", "8080" };
    int argc = 6;
    Mock<rsi::uploader::ParametersInterface> mock;
    When(Method(mock, parameters))
        .AlwaysDo(
            [](int, char const* []) {
                return rsi::Parameters();
            });

    rsi::uploader::ParametersInterface& i = mock.get();
    REQUIRE(i.parameters(argc, argv) == rsi::Parameters());
    Verify(Method(mock, parameters));
}
