#ifndef _EXPARX_PARCEL_HPP
#define _EXPARX_PARCEL_HPP

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/exceptions.hpp>
#include <extras/crcs.hpp>
#include <rsi/parcel/v2/Exceptions.hpp>
#include <rsi/parcel/v2/Line.hpp>
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

            virtual const Parameter& parcel() const pure;
            virtual const Parameter& packed() const pure;
            virtual const Parameter& unpacked() const pure;

            virtual void pack() pure;
            virtual void unpack()  pure;

        };



    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_PARCEL_HPP
