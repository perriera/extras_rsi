#include <rsi/vendor/Vendor.hpp>
#include <iostream>
#include <extras/status/StatusLine.hpp>

using namespace std;

namespace extras {

    /**
     *  @brief Vendor Client/Server ::transfer()
     *
     */
    void rsi::VendorClient::transfer() const {
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(" processed") << std::endl;
    }


}  // namespace extras
