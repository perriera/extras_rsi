#include <rsi/vendor/Vendor.hpp>
#include <iostream>
#include <rsi/sockets/StatusLine.hpp>

using namespace std;

namespace extras {

    /**
     *  @brief Vendor Client/Server ::transfer()
     *
     */
    void rsi::VendorClient::transfer() const {
        std::cout << rsi::pass(filename()) << std::endl;
        std::cout << rsi::pass(" processed") << std::endl;
    }


}  // namespace extras
