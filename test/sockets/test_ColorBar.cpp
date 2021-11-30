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
#include <extras/strings.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"

using namespace extras;

//
// printf("[+]File data downloaded successfully.\n");
//

SCENARIO("Test ColorStatusBar", "[StatusBarInterface]") {

    rsi::ColorStatusBar testcase;

    rsi::StatusBarInterface& i = testcase;
    i.bar(25, 50);

    for (int c = 0;c < 1000;c++)
        std::cout << i.bar(c, 1000) << std::flush;
    std::cout << std::endl;
}
