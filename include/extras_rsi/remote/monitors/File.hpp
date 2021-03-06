/**
 * @file Monitor.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief Monitor
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSI_MONITOR_FILE_HPP
#define _EXPARX_RSI_MONITOR_FILE_HPP

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
#include <extras_rsi/remote/CausalityInterface.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief Monitor
         *
         */
        concrete class FileMonitor implements CausalityInterface {

        protected:
            Pathname _pathname;
            int _watchDog = 2;

        public:

            FileMonitor() {}
            FileMonitor(const Pathname& pathname, int watchDog = 2)
                :_pathname(pathname), _watchDog(watchDog) {}

            /**
             * @brief CausalityInterface
             *
             */
            virtual void cause() override;
            virtual void effect() override;
            virtual void reset() override;

        };

        /**
         * @brief
         *
         */
        concrete class PassiveFileMonitor extends FileMonitor {

            std::chrono::_V2::system_clock::time_point _timeMarker;

        public:

            PassiveFileMonitor() {}
            PassiveFileMonitor(const Pathname& pathname, int watchDog = 2);

            /**
             * @brief CausalityInterface
             *
             */
            virtual void cause() override;
        };


    }
}

#endif // _EXPARX_RSI_MONITOR_FILE_HPP


