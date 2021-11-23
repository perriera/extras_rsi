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
