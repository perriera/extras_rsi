#ifndef _EXPARX_RSISERVICES_PARCEL_HPP
#define _EXPARX_RSISERVICES_PARCEL_HPP

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {
        /**
         * @brief ParcelInterface
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */

        interface ParcelInterface {

            virtual const Parameter& payload() const pure;
            virtual const Parameter& parcel() const pure;

            /**
             * @brief connect()
             * @note do whatever socket connection is required, (using the parameters
             * collected earlier)
             */
            virtual void pack() pure;

            /**
             * @brief transfer()
             * @note this is where the magic happens, depending what type of class you
             * are this method performs the data transfer, (or initiates it)
             */
            virtual void unpack()  pure;

        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_PARCEL_HPP
