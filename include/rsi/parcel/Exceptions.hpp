/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * The above copyright notice and  this permission  notice shall be
 * included in all copies or  substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESSED  OR   IMPLIED,  INCLUDING   BUT  NOT  LIMITED  TO  THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT.  IN  NO  EVENT  SHALL EXPARX  INCORPORATED
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER  IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM, OUT  OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR  OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Except  as  contained  in this  notice, the  name of  the EXPARX
 * INCORPORATED shall not  be used in  advertising or  otherwise to
 * promote the sale, use or other dealings in this Software without
 * prior written authorization from EXPARX INCORPORATED.
 *
 * exparx.com and www.exparx.com  are domain names  registered with
 * EXPARX INCORPORATED, (other GPL-themed licenses are included).
 *
 */

#ifndef _EXPARX_PARCEL_EXCEPTIONS_HPP
#define _EXPARX_PARCEL_EXCEPTIONS_HPP

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/exceptions.hpp>
#include <extras/crcs.hpp>
#include <rsi/parcel/Line.hpp>
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
                if (delimiter != ':' && delimiter != '/')
                    throw ParcelException("Bad delimiter:" + delimiter, ref);
            }
            static void assertion(const PackedLine& line1, const PackedLine& line2, const extras::WhereAmI& ref) {
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
                rsi::PackedLine check(0, 0, hexLine);
                if (check.checksum() != crc)
                    throw ParcelException("Bad CRC:" + hexLine, ref);
            }

            static void assertion(const Filename& parcel, const Filename& unpacked, const extras::WhereAmI& ref);
        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_PARCEL_EXCEPTIONS_HPP

