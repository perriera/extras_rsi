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
        send_line(msg, this->_sockfd);

        std::string line = read_line(this->_sockfd);
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(line) << std::endl;

    }


}  // namespace extras
