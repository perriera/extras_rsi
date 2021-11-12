#include <rsi/vendor/Vendor.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        void VendorServer::connect() {
            _proxy.connect();
        }
        void VendorServer::transfer() {
            system("ls -la");
            _proxy.transfer();
            system("ls -la");
            deliverParcel();
        }
        void VendorServer::close() {
            _proxy.close();
        }

    }
}  // namespace extras
