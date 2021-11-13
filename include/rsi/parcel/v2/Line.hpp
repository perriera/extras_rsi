#ifndef _EXPARX_PARCELLINE_HPP
#define _EXPARX_PARCELLINE_HPP

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/exceptions.hpp>
#include <extras/crcs.hpp>
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

        using CRC = u_int16_t;

        interface ParcelLineInterface {
            virtual  int lineNo() const pure;
            virtual const HexLine& hexLine() const pure;
            virtual const CRC& checksum() const pure;

            bool operator==(const ParcelLineInterface& rhs) const {
                return hexLine() == rhs.hexLine() && checksum() == rhs.checksum();
            }

            bool operator!=(const ParcelLineInterface& rhs) const {
                return !(*this == rhs);
            }
        };

        concrete class ParcelLine implements ParcelLineInterface {
            friend std::ostream& operator<<(std::ostream& out, const ParcelLine& obj);
            friend std::istream& operator>>(std::istream& in, ParcelLine& obj);
            int _lineNo;
            HexLine _hexLine;
            CRC _crc = 0;
        public:
            ParcelLine() {};
            ParcelLine(int lineNo, const HexLine& hexLine) :
                _lineNo(lineNo), _hexLine(hexLine) {
                _crc = crc16().update(_hexLine);
            };
            virtual  int lineNo() const override { return _lineNo; };
            virtual const HexLine& hexLine() const override { return _hexLine; };
            virtual const CRC& checksum() const override { return _crc; };
        };

        using ParcelFile = std::vector<ParcelLine>;

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_PARCELLINE_HPP
