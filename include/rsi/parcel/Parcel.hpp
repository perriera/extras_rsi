#ifndef _EXPARX_RSISERVICES_PARCEL_HPP
#define _EXPARX_RSISERVICES_PARCEL_HPP

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/bin2hex/ConvertFile.hpp>
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

        interface ParcelInterface {

            virtual const Parameter& payload() const pure;
            virtual const Parameter& parcel() const pure;
            virtual Parameter payload_unpacked() const pure;
            virtual HexFile hexFile() const pure;

            // virtual const ParcelFile& parcelFile() const pure;
            // virtual void set(const ParcelFile&) pure;

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

            virtual void check_packaging() const pure;
            virtual void compare() const pure;


        };

        concrete class Parcel implements ParcelInterface {
            friend std::ostream& operator<<(std::ostream& out, const Parcel& obj);
            friend std::istream& operator>>(std::istream& in, Parcel& obj);

            Parameter _payload;
            Parameter _parcel;
            ParcelFile _parcelFile;

        public:
            Parcel() {}
            Parcel(const Parameter& payload, const Parameter& parcel) :_payload(payload), _parcel(parcel) {}
            virtual const Parameter& payload() const override { return _payload; };
            virtual const Parameter& parcel() const override { return _parcel; };
            virtual Parameter payload_unpacked() const override { return _payload + ".unpacked"; };
            virtual HexFile hexFile() const override;

            /**
             * @brief connect()
             * @note do whatever socket connection is required, (using the parameters
             * collected earlier)
             */
            virtual void pack() override;

            /**
             * @brief transfer()
             * @note this is where the magic happens, depending what type of class you
             * are this method performs the data transfer, (or initiates it)
             */
            virtual void unpack()  override;

            virtual void check_packaging() const override;
            virtual void compare() const override;

        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_PARCEL_HPP
