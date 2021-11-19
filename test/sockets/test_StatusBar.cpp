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

    rsi::StatusBarMsg good = "[+] 25 / 50\n";
    rsi::StatusBar testcase;

    rsi::StatusBarInterface& i = testcase;
    REQUIRE(i.bar(25, 50) == good);
}
