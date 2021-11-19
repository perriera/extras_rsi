#ifndef _EXPARX_RSISTATUSBAR_HPP
#define _EXPARX_RSISTATUSBAR_HPP

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <iostream>
#include <rsi/exceptions.hpp>

namespace extras {
    namespace rsi {

        /**
         * @brief StatusBarInterface
         *
         */

        using StatusBarMsg = std::string;

        interface StatusBarInterface {

            virtual StatusBarMsg bar(int count, int max) const pure;

        };

        concrete class StatusBar implements StatusBarInterface {
        public:

            virtual StatusBarMsg bar(int count, int max) const override;

            static int linesInFile(const std::string& filename);
            static int lastLinesInFile;
        };

        /**
         * @brief start std::ostream& manipulator
         *
         */
        class bar
        {
            friend std::ostream& operator<<(std::ostream& out, const bar& obj) {
                out << StatusBar().bar(obj._count, obj._max);
                return out;
            }
        public:
            bar(int count, int max) : _count(count), _max(max) {}
            std::ostream& operator()(std::ostream& out) const {
                out << StatusBar().bar(_count, _max);
                return out;
            }
            virtual int count() const { return _count; };
            virtual int max() const { return _max; };

        private:
            int _count;
            int _max;
        };

        /**
         * @brief StatusBarException
         *
         */
        concrete class StatusBarException extends RSIException {
        public:
            StatusBarException(std::string msg, const extras::WhereAmI& whereAmI)
                : RSIException(msg.c_str(), whereAmI) {}
            static void assertion(int status, const extras::WhereAmI& ref);
        };

    }
}

#endif // _EXPARX_RSISTATUSBAR_HPP


