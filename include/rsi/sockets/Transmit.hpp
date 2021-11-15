#ifndef _EXPARX_RSISUBSYSTEM_TRANSMIT_HPP
#define _EXPARX_RSISUBSYSTEM_TRANSMIT_HPP

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <iostream>
#include <rsi/exceptions.hpp>

namespace extras {
    namespace rsi {

        /**
         * @brief TransmitInterface
         *
         */

        using TransmitMsg = std::string;

        interface TransmitInterface {

            virtual int socket() const pure;
            virtual int transmit_size() const pure;

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
            virtual int send(const TransmitMsg& msg) const pure;
            virtual TransmitMsg read() const pure;

        };

        /**
         * @brief TransmitInterface
         *
         */

        using BurstArray = std::vector<TransmitMsg>;

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
        concrete class TransmitException extends RSIException {
        public:
            TransmitException(std::string msg, const extras::WhereAmI& whereAmI)
                : RSIException(msg.c_str(), whereAmI) {}
            static void assertion(int status, const extras::WhereAmI& ref) {
                if (status < 0)
                    throw TransmitException("Error Code: " + std::to_string(status), ref);
            }
        };

    }
}

#endif // _EXPARX_RSISUBSYSTEM_TRANSMIT_HPP


