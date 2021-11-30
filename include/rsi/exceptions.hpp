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

#ifndef _EXPARX_RSI_EXCEPTIONS_HPP
#define _EXPARX_RSI_EXCEPTIONS_HPP

 /**
  * @file exceptions.hpp
  * @author Perry Anderson (perryanderson.com)
  * @brief Adds extra keywords for C++ applications
  * @version 1.2.1
  * @date 2021-07-25
  *
  * @copyright Copyright (c) 2021 Perry Anderson,
  * All Rights Reserved, MIT License.
  *
  */

#include <extras/interfaces.hpp>

namespace extras {

    namespace rsi {

        /**
         * @brief RSIException
         *
         */
        concrete class RSIException extends extras::AbstractCustomException {
        public:
            RSIException(const char* msg, const extras::WhereAmI& whereAmI)
                : extras::AbstractCustomException(msg, whereAmI._file.c_str(),
                    whereAmI._func.c_str(), whereAmI._line) {}
            static void assertion(const std::string& msg, const extras::WhereAmI& ref);
        };

        concrete class SocketException extends RSIException {
        public:
            SocketException(std::string msg, const extras::WhereAmI& whereAmI)
                : RSIException(msg.c_str(), whereAmI) {}
            static void assertionLTZero(int error, const std::string& msg, const extras::WhereAmI& ref) {
                if (error < 0)
                    throw SocketException(msg, ref);
            }
            static void assertionNEZero(int error, const std::string& msg, const extras::WhereAmI& ref) {
                if (error != 0)
                    throw SocketException(msg, ref);
            }
            static void assertionLTMinusOne(int error, const std::string& msg, const extras::WhereAmI& ref) {
                if (error < -1)
                    throw SocketException(msg, ref);
            }
            static void assertionNEMinusOne(int error, const std::string& msg, const extras::WhereAmI& ref) {
                if (error != -1)
                    throw SocketException(msg, ref);
            }
            static void assertionEQMinusOne(int error, const std::string& msg, const extras::WhereAmI& ref) {
                if (error == -1)
                    throw SocketException(msg, ref);
            }
        };

        /**
         * @brief UnsupportedTokenException
         *
         */
        concrete class UnsupportedTokenException extends RSIException {
        public:
            UnsupportedTokenException(std::string msg, const extras::WhereAmI& whereAmI)
                : RSIException(msg.c_str(), whereAmI) {}
            static void assertion(const std::string& msg, const extras::WhereAmI& ref) {
                if (msg.length() == 0) throw UnsupportedTokenException(msg, ref);
            }
        };

        /**
         * @brief NoTokensException
         *
         */
        concrete class NoTokensException extends RSIException {
        public:
            NoTokensException(const extras::WhereAmI& whereAmI)
                : RSIException("No tokens were specified", whereAmI) {}
            static void assertion(int size, const extras::WhereAmI& ref) {
                if (size == 0) throw NoTokensException(ref);
            }
        };

        /**
         * @brief FileNotFoundException
         *
         */
        concrete class FileNotFoundException extends RSIException {
        public:
            FileNotFoundException(std::string msg, const extras::WhereAmI& whereAmI)
                : RSIException(msg.c_str(), whereAmI) {}
            static void assertion(const std::string& filename, const extras::WhereAmI& ref);
        };

        /**
         * @brief CantOpenFileException
         *
         */
        concrete class CantOpenStreamException extends RSIException {
        public:
            CantOpenStreamException(std::string msg, const extras::WhereAmI& whereAmI)
                : RSIException(msg.c_str(), whereAmI) {}
            static void assertion(const std::istream& stream, const std::string& filename, const extras::WhereAmI& ref);
            static void assertion(const std::ostream& stream, const std::string& filename, const extras::WhereAmI& ref);
        };

        /**
         * @brief CantOpenFileException
         *
         */
        concrete class RemoteDiedException extends RSIException {
        public:
            RemoteDiedException(std::string msg, const extras::WhereAmI& whereAmI)
                : RSIException(msg.c_str(), whereAmI) {}
            static void assertion(const std::string& response, const extras::WhereAmI& ref);
        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSI_EXCEPTIONS_HPP