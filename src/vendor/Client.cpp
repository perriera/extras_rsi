#include <rsi/vendor/Vendor.hpp>
#include <iostream>
#include <extras/status/StatusLine.hpp>
#include <rsi/subsystem.hpp>

using namespace std;

namespace extras {

    /**
     *  @brief Vendor Client/Server ::transfer()
     *
     */
    void rsi::VendorClient::transfer() const {

        std::string msg = "vendor started";
        send_line(msg);
        std::string status = read_line();
        RemoteDiedException::assertion(status, __INFO__);
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(status) << std::endl;

    }


}  // namespace extras
