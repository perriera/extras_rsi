#include <rsi/sockets/StatusBar.hpp>
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

    rsi::StatusBarMsg good = "[+] 25 / 50\n";
    Mock<rsi::StatusBarInterface> mock;
    When(Method(mock, bar))
        .AlwaysDo(
            [](int count, int max) {
                std::stringstream ss;
                ss << "[+] " << count << " / " << max << std::endl;
                return ss.str();
            });

    rsi::StatusBarInterface& i = mock.get();
    REQUIRE(i.bar(25, 50) == good);
    Verify(Method(mock, bar));
}
