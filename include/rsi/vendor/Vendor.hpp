#ifndef _EXPARX_RSISERVICES_VENDOR_HPP
#define _EXPARX_RSISERVICES_VENDOR_HPP

#include <extras/interfaces.hpp>
#include <rsi/uploader/Uploader.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {

        /**
         * @brief concrete class VendorClient
         *
         */
        concrete class VendorClient extends UploaderClient {
        public:
            virtual void transfer() const override;
        };

        /**
         * @brief concrete class VendorServer
         *
         */
        concrete class VendorServer extends UploaderServer {
        public:
            virtual void transfer() const override;
        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_VENDOR_HPP
