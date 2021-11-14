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

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSI_EXCEPTIONS_HPP