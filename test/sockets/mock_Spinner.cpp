#include <rsi/sockets/Spinner.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock SpinnerInterface", "[SpinnerInterface]") {

    rsi::SpinnerMsg good = "[/]";
    Mock<rsi::SpinnerInterface> mock;
    When(Method(mock, spinner))
        .AlwaysDo(
            [](int index) {
                std::stringstream ss;
                std::string spinner = "|/-\\";
                char c = spinner[index % spinner.size()];
                ss << extras::green << "\r[";
                ss << extras::yellow << c;
                ss << extras::green << "]";
                return ss.str();
            });

    rsi::SpinnerInterface& i = mock.get();
    auto x = i.spinner(25);
    auto y = i.spinner(24);
    auto z = i.spinner(26);
    REQUIRE(x == "\033[32m\r[\033[33m/\033[32m]");
    REQUIRE(y == "\033[32m\r[\033[33m|\033[32m]");
    REQUIRE(z == "\033[32m\r[\033[33m-\033[32m]");
    Verify(Method(mock, spinner));
}
