
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"
#include <rsi/sockets/PortAuthority.hpp>

using namespace exparx;
using namespace fakeit;

SCENARIO("Mock PortAuthorityInterface", "[PortAuthorityInterface]") {
    int correct_request = 9000;
    Mock<rsi::PortAuthorityInterface> mock;
    When(Method(mock, request)).Return(correct_request);

    rsi::PortAuthorityInterface& i = mock.get();
    REQUIRE(i.request() == correct_request);
    Verify(Method(mock, request));
}
