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