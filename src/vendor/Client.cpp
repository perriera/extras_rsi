#include <rsi/uploader/Vendor.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        void VendorClient::connect() {
            _proxy.connect();
            wrapParcel();
        }
        void VendorClient::transfer() {
            _proxy.transfer();
        }
        void VendorClient::close() {
            _proxy.close();
            unwrapParcel();
        }

    }
}  // namespace extras
