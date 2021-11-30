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

#include <rsi/sockets/StatusBar.hpp>
#include <rsi/sockets/Spinner.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

//
// printf("[+]File data downloaded successfully.\n");
//

SCENARIO("Mock StatusBarInterface", "[StatusBarInterface]") {

    rsi::StatusBarMsg good = "\033[32m\r[\033[33m+\033[32m] 25 / 50\n";
    Mock<rsi::StatusBarInterface> mock;
    When(Method(mock, bar))
        .AlwaysDo(
            [](int count, int max) {
                std::stringstream ss;
                ss << rsi::spinner(count) << " ";
                ss << count << " / " << max << std::endl;
                auto x = ss.str();
                return ss.str();
            });

    rsi::StatusBarInterface& i = mock.get();
    REQUIRE(i.bar(25, 50) == good);
    Verify(Method(mock, bar));
}
