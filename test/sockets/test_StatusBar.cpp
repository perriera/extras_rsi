#include <rsi/sockets/StatusBar.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"

using namespace extras;

//
// printf("[+]File data downloaded successfully.\n");
//

SCENARIO("Test StatusBarInterface", "[StatusBarInterface]") {

    rsi::StatusBarMsg good = "[+] 26 / 50";
    rsi::StatusBar testcase;

    rsi::StatusBarInterface& i = testcase;
    REQUIRE(i.bar(25, 50) == good);

    for (int c = 0;c < 1000;c++)
        std::cout << "\r" << i.bar(c, 1000) << std::flush;
    std::cout << std::endl;
}
