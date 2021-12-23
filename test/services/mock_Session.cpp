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

#include <extras_rsi/services/SessionType.hpp>
#include <extras_rsi/socketpool/Parameters.hpp>
#include <extras_rsi/socketpool/Client.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;


SCENARIO("Mock SessionInterface: clients", "[SessionInterface]") {

    rsi::RequestType requestType = "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip";
    extras::Directory directory = "/tmp/token";

    Mock<rsi::SessionInterface> mock;
    When(Method(mock, make))
        .AlwaysDo(
            [&directory]() {
                return  directory;
            });

    rsi::SessionInterface& i = mock.get();
    REQUIRE(i.make() == directory);
    Verify(Method(mock, make));

}
