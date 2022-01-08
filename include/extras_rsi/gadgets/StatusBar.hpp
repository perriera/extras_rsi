/**
 * @file StatusBar.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief StatusBarInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISTATUSBAR_HPP
#define _EXPARX_RSISTATUSBAR_HPP

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
#include <extras_rsi/remote/sockets/Types.hpp>
#include <iostream>
#include <extras_rsi/exceptions.hpp>

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

        concrete class ColorStatusBar implements StatusBarInterface {
        public:

            virtual StatusBarMsg bar(int count, int max) const override;

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


