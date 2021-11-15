#include <rsi/uploader/Vendor.hpp>
#include <rsi/sockets/Burst.hpp>
#include <extras/strings.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock BurstInterface", "[BurstInterface]") {

    rsi::BurstArray msg = { "Hello World" };
    rsi::BurstArray buffer;
    Mock<rsi::BurstInterface> mock;
    When(Method(mock, source))
        .AlwaysDo(
            [&buffer](const rsi::BurstArray& msg) {
                buffer = msg;
                return buffer.size();
            });

    rsi::BurstInterface& i = mock.get();
    REQUIRE(i.source(msg) == msg.size());
    REQUIRE(msg == buffer);
    Verify(Method(mock, source));
}

SCENARIO("Mock BurstInterface: fail", "[BurstInterface]") {

    rsi::BurstArray msg = { "Hello World" };
    rsi::BurstArray buffer;
    Mock<rsi::BurstInterface> mock;
    When(Method(mock, source))
        .AlwaysDo(
            [&buffer](const rsi::BurstArray&) {
                rsi::BurstException::assertion(-1, __INFO__);
                return -1;
            });

    rsi::BurstInterface& i = mock.get();
    REQUIRE_THROWS_AS(i.source(msg), rsi::BurstException);
    REQUIRE(msg != buffer);
    Verify(Method(mock, source));
}

SCENARIO("Mock BurstInterface: Send/Read", "[BurstInterface]") {

    rsi::BurstArray burstArray = { "Hello World", "Data Line", "Another line" };
    std::stringstream ss;
    Mock<rsi::BurstInterface> mock;
    When(Method(mock, source))
        .AlwaysDo(
            [&ss](const rsi::BurstArray& array) {
                ss << array.size() << std::endl;
                for (auto item : array)
                    ss << item << std::endl;
                return ss.str().size();
            });
    When(Method(mock, sink))
        .AlwaysDo(
            [&ss]() {
                rsi::BurstArray array;
                int count = 0;
                ss >> std::skipws >> count;
                std::string msg;
                std::getline(ss, msg);
                while (count-- > 0 && ss.good()) {
                    std::getline(ss, msg);
                    if (ss.good())
                        array.push_back(msg);
                }
                return array;
            });

    rsi::BurstInterface& i = mock.get();
    auto count = i.source(burstArray);
    REQUIRE(count == ss.str().size());
    REQUIRE(i.sink() == burstArray);
    Verify(Method(mock, source));
    Verify(Method(mock, sink));
}
