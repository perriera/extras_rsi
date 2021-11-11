#ifndef _EXPARX_RSISERVICES_UPLOADER_HPP
#define _EXPARX_RSISERVICES_UPLOADER_HPP

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {
        /**
         * @brief UploaderInterface
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */

        interface VendorInterface {

            /**
             * @brief add_value()
             *
             * @note at this point the file in question to be operated on
             * has now been successfully uploaded to the server and it is
             * up to the vendor to do something withit. As soon as this
             * method completes the file specifed under filename is
             * considered changed and will be automatically downloaded
             * back to the client. For simplicity, the same filename will
             * be used. This makes it easier for the support system to
             * remove the file as soon as it has been successfully
             * downloaded back to the client.
             *
             * @param filename
             */
            virtual void add_value(const Filename& filename) pure;

        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_UPLOADER_HPP
