/**
 * @file Spinner.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief SpinnerInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISTATUSSPINNER_HPP
#define _EXPARX_RSISTATUSSPINNER_HPP

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
  * (See LICENSE.md for complete details)
  *
  */

#include <extras/interfaces.hpp>
#include <extras_rsi/sockets/Types.hpp>
#include <iostream>
#include <extras_rsi/exceptions.hpp>

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


