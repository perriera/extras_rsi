#include <rsi/uploader/Vendor.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        void VendorServer::connect() {
            _proxy.connect();
        }
        void VendorServer::transfer() {
            _proxy.transfer();
            deliverParcel();
        }
        void VendorServer::close() {
            _proxy.close();
        }

    }
}  // namespace extras
