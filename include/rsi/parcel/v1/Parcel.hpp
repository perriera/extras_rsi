#ifndef _EXPARX_RSISERVICES_PARCEL_HPP
#define _EXPARX_RSISERVICES_PARCEL_HPP

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


        /**
         * @brief ParcelLineException
         *
         */
        concrete class ParcelLineException extends RSIException {
        public:
            ParcelLineException(std::string msg, const extras::WhereAmI& whereAmI)
                : RSIException(msg.c_str(), whereAmI) {}
            static void assertion(char delimiter, const extras::WhereAmI& ref) {
                if (delimiter != ':')
                    throw ParcelLineException("Bad delimiter:" + delimiter, ref);
            }
            static void assertion(const ParcelLine& line1, const ParcelLine& line2, const extras::WhereAmI& ref) {
                if (line1 != line2)
                    throw ParcelLineException("Corrupted save on line:" + std::to_string(line1.lineNo()), ref);
            }
            static void assertion(const BinLine& line1, const BinLine& line2, int line, const extras::WhereAmI& ref) {
                if (line1 != line2)
                    throw ParcelLineException("Corrupted save on line:" + std::to_string(line), ref);
            }
            static void assertion(int line_no, const extras::WhereAmI& ref) {
                if (line_no < 0)
                    throw ParcelLineException("Bad line number:" + std::to_string(line_no), ref);
            }
            static void assertion(int line_no1, int line_no2, const extras::WhereAmI& ref) {
                if (line_no1 != line_no2)
                    throw ParcelLineException("Line number out of sync:"
                        + std::to_string(line_no1) + std::to_string(line_no2), ref);
            }
            static void assertion(rsi::HexLine hexLine, const extras::WhereAmI& ref) {
                for (auto c : hexLine)
                    if (!isxdigit(c))
                        throw ParcelLineException("Bad HexLine:" + hexLine, ref);
            }
            static void assertion(rsi::CRC crc, rsi::HexLine hexLine, const extras::WhereAmI& ref) {
                rsi::ParcelLine check(0, hexLine);
                if (check.checksum() != crc)
                    throw ParcelLineException("Bad CRC:" + hexLine, ref);
            }
        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_PARCEL_HPP
