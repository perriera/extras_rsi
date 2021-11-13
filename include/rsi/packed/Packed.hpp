#ifndef _EXPARX_PARCEL_HPP
#define _EXPARX_PARCEL_HPP

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/exceptions.hpp>
#include <extras/crcs.hpp>
#include <rsi/packed/Exceptions.hpp>
#include <rsi/packed/Line.hpp>
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


        interface PackedInterface {

            virtual BinFile loadBin(const Filename& filename) const pure;
            virtual HexFile convertToHex() const pure;
            virtual HexFile hexFile() const pure;

            virtual const Parameter& parcel() const pure;
            virtual const Parameter& hexed() const pure;
            virtual const Parameter& packed() const pure;
            virtual const Parameter& unpacked() const pure;

            virtual void pack() const pure;
            virtual void unpack() const pure;
            virtual void verify_integrity() const pure;

        };



    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_PARCEL_HPP
