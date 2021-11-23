#ifndef _EXPARX_RSISTATUSSPINNER_HPP
#define _EXPARX_RSISTATUSSPINNER_HPP

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

        using SpinnerMsg = std::string;

        interface SpinnerInterface {

            virtual SpinnerMsg spinner(int index) const pure;

        };

        concrete class Spinner implements SpinnerInterface {
        public:

            virtual SpinnerMsg spinner(int index = 0) const override;

        };

        /**
         * @brief start std::ostream& manipulator
         *
         */
        class spinner
        {
            friend std::ostream& operator<<(std::ostream& out, const spinner& obj) {
                out << Spinner().spinner(obj._index);
                return out;
            }
        public:
            spinner(int index) : _index(index) {}
            std::ostream& operator()(std::ostream& out) const {
                out << Spinner().spinner(_index);
                return out;
            }

        private:
            int _index;
        };


    }
}

#endif // _EXPARX_RSISTATUSSPINNER_HPP


