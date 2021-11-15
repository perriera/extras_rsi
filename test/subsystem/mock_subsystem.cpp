#include <rsi/uploader/Vendor.hpp>
#include <rsi/sockets/Transmit.hpp>
#include <extras/strings.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock TransmitInterface", "[TransmitInterface]") {

    rsi::TransmitMsg msg = "Hello World";
    std::string buffer;
    Mock<rsi::TransmitInterface> mock;
    When(Method(mock, send))
        .AlwaysDo(
            [&buffer](const rsi::TransmitMsg& msg) {
                buffer = msg;
                return buffer.size();
            });

    rsi::TransmitInterface& i = mock.get();
    REQUIRE(i.send(msg) == msg.size());
    REQUIRE(msg == buffer);
    Verify(Method(mock, send));
}

SCENARIO("Mock TransmitInterface: fail", "[TransmitInterface]") {

    rsi::TransmitMsg msg = "Hello World";
    std::string buffer;
    Mock<rsi::TransmitInterface> mock;
    When(Method(mock, send))
        .AlwaysDo(
            [&buffer](const rsi::TransmitMsg&) {
                rsi::TransmitException::assertion(-1, __INFO__);
                return -1;
            });

    rsi::TransmitInterface& i = mock.get();
    REQUIRE_THROWS_AS(i.send(msg), rsi::TransmitException);
    REQUIRE(msg != buffer);
    Verify(Method(mock, send));
}

SCENARIO("Mock TransmitInterface: Send/Read", "[TransmitInterface]") {

    rsi::TransmitMsg msg = "Hello World";
    std::stringstream ss;
    Mock<rsi::TransmitInterface> mock;
    When(Method(mock, send))
        .AlwaysDo(
            [&ss](const rsi::TransmitMsg& msg) {
                ss << msg << std::endl;
                return ss.str().size();
            });
    When(Method(mock, read))
        .AlwaysDo(
            [&ss]() {
                std::string msg;
                std::getline(ss, msg);
                return msg;
            });

    rsi::TransmitInterface& i = mock.get();
    auto count = i.send(msg);
    REQUIRE(count == ss.str().size());
    REQUIRE(i.read() == msg);
    Verify(Method(mock, send));
}
