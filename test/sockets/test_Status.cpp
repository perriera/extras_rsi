#include <rsi/sockets/Status.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"

using namespace extras;

//
// printf("[+]File data downloaded successfully.\n");
//

SCENARIO("Test StatusLineInterface", "[StatusLineInterface]") {

    rsi::StatusMsg good = "File data downloaded successfully";
    rsi::StatusMsg bad = "Error in socket";
    rsi::StatusLine testcase;

    rsi::StatusLineInterface& i = testcase;
    REQUIRE(extras::contains(i.pass(good), good));
    REQUIRE(extras::contains(i.fail(bad), bad));
}
