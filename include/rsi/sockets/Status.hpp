#ifndef _EXPARX_RSISTATUS_HPP
#define _EXPARX_RSISTATUS_HPP

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

        using StatusMsg = std::string;

        interface StatusLineInterface {

            virtual StatusMsg pass(const StatusMsg& msg) const pure;
            virtual StatusMsg fail(const StatusMsg& msg) const pure;

        };

        concrete class StatusLine implements StatusLineInterface {
        public:

            virtual StatusMsg pass(const StatusMsg& msg) const override;
            virtual StatusMsg fail(const StatusMsg& msg) const override;

        };

        /**
         * @brief pass std::ostream& manipulator
         *
         */
        class pass
        {
        public:
            pass(const StatusMsg& msg) : _msg(msg) {}
            std::ostream& operator()(std::ostream& out) const {
                out << StatusLine().pass(_msg);
                return out;
            }
        private:
            StatusMsg _msg;
        };

        /**
         * @brief fail std::ostream& manipulator
         *
         */
        class fail
        {
        public:
            fail(const StatusMsg& msg) : _msg(msg) {}
            std::ostream& operator()(std::ostream& out) const {
                out << StatusLine().fail(_msg);
                return out;
            }
        private:
            StatusMsg _msg;
        };





        /**
         * @brief PackedException
         *
         */
        concrete class StatusLineException extends RSIException {
        public:
            StatusLineException(std::string msg, const extras::WhereAmI& whereAmI)
                : RSIException(msg.c_str(), whereAmI) {}
            static void assertion(int status, const extras::WhereAmI& ref);
        };

    }
}

#endif // _EXPARX_RSISUBSYSTEM_BURST_HPP


