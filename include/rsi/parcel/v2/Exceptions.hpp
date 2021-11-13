#ifndef _EXPARX_PARCEL_EXCEPTIONS_HPP
#define _EXPARX_PARCEL_EXCEPTIONS_HPP

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/exceptions.hpp>
#include <extras/crcs.hpp>
#include <rsi/parcel/v2/Line.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {


        /**
         * @brief ParcelException
         *
         */
        concrete class ParcelException extends RSIException {
        public:
            ParcelException(std::string msg, const extras::WhereAmI& whereAmI)
                : RSIException(msg.c_str(), whereAmI) {}
            static void assertion(char delimiter, const extras::WhereAmI& ref) {
                if (delimiter != ':')
                    throw ParcelException("Bad delimiter:" + delimiter, ref);
            }
            static void assertion(const ParcelLine& line1, const ParcelLine& line2, const extras::WhereAmI& ref) {
                if (line1 != line2)
                    throw ParcelException("Corrupted save on line:" + std::to_string(line1.lineNo()), ref);
            }
            static void assertion(const BinLine& line1, const BinLine& line2, int line, const extras::WhereAmI& ref) {
                if (line1 != line2)
                    throw ParcelException("Corrupted save on line:" + std::to_string(line), ref);
            }
            static void assertion(int line_no, const extras::WhereAmI& ref) {
                if (line_no < 0)
                    throw ParcelException("Bad line number:" + std::to_string(line_no), ref);
            }
            static void assertion(int line_no1, int line_no2, const extras::WhereAmI& ref) {
                if (line_no1 != line_no2)
                    throw ParcelException("Line number out of sync:"
                        + std::to_string(line_no1) + std::to_string(line_no2), ref);
            }
            static void assertion(rsi::HexLine hexLine, const extras::WhereAmI& ref) {
                for (auto c : hexLine)
                    if (!isxdigit(c))
                        throw ParcelException("Bad HexLine:" + hexLine, ref);
            }
            static void assertion(rsi::CRC crc, rsi::HexLine hexLine, const extras::WhereAmI& ref) {
                rsi::ParcelLine check(0, hexLine);
                if (check.checksum() != crc)
                    throw ParcelException("Bad CRC:" + hexLine, ref);
            }
        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_PARCEL_EXCEPTIONS_HPP
