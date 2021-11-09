#ifndef _EXTRA_RSISOCKETSEXCEPTIONS_HPP
#define _EXTRA_RSISOCKETSEXCEPTIONS_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <extras/interfaces.hpp>

namespace exparx {

    namespace rsi {

        /**
         * @brief SocketException
         *
         * To be thrown if either string or value supplied is out of range.
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
         * @brief SocketException
         *
         * To be thrown if either string or value supplied is out of range.
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

        concrete class NoTokensException extends RSIException {
        public:
            NoTokensException(const extras::WhereAmI& whereAmI)
                : RSIException("No tokens were specified", whereAmI) {}
            static void assertion(int size, const extras::WhereAmI& ref) {
                if (size == 0) throw NoTokensException(ref);
            }
        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXTRA_RSISOCKETSEXCEPTIONS_HPP
