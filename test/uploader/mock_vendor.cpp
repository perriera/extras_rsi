#include <rsi/uploader/Vendor.hpp>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock VendorInterface", "[VendorInterface]") {

    rsi::Filename filename = "send.txt";
    const char* argv[] = { "socketclient", "127.0.0.1", "8080",
                            filename.c_str(),     "convert",   "download" };
    int argc = 6;
    Mock<rsi::VendorInterface> mock;
    When(Method(mock, add_value))
        .AlwaysDo(
            [](const rsi::Filename& filename) {

            });

    rsi::VendorInterface& i = mock.get();
    i.add_value(filename);
    Verify(Method(mock, add_value));
}
