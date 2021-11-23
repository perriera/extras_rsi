#include <rsi/sockets/Spinner.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Test SpinnerInterface", "[SpinnerInterface]") {

    rsi::SpinnerMsg good = "[/]";

    for (int i = 0; i < 1000; i++)
        std::cout << "\r" << rsi::spinner(i) << std::flush;

    std::stringstream ss;
    ss << rsi::spinner(0);
    std::string text = ss.str();

    REQUIRE(text == "\033[32m\r[\033[33m+\033[32m]");

}
