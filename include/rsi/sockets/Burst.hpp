#ifndef _EXPARX_RSISUBSYSTEM_BURST_HPP
#define _EXPARX_RSISUBSYSTEM_BURST_HPP

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <iostream>
#include <rsi/exceptions.hpp>

namespace extras {
    namespace rsi {

        /**
         * @brief BurstInterface
         *
         */

        using BurstArray = std::vector<std::string>;

        interface BurstInterface {

            virtual int socket() const pure;
            virtual int burst_size() const pure;

            /**
             * @brief send()
             * Send N bytes of BUF to socket FD.  Returns the number sent or -1.
               This function is a cancellation point and therefore not marked with
               __THROW.
             *
             * @param __fd
             * @param __buf
             * @param __n
             * @param __flags
             * @return int
             */
            virtual int source(const BurstArray& msg) const pure;
            virtual BurstArray sink() const pure;

        };

        /**
         * @brief PackedException
         *
         */
        concrete class BurstException extends RSIException {
        public:
            BurstException(std::string msg, const extras::WhereAmI& whereAmI)
                : RSIException(msg.c_str(), whereAmI) {}
            static void assertion(int status, const extras::WhereAmI& ref) {
                if (status < 0)
                    throw BurstException("Error Code: " + std::to_string(status), ref);
            }
        };

    }
}

#endif // _EXPARX_RSISUBSYSTEM_BURST_HPP


