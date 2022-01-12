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

#ifndef _EXPARX_RSI_MONITOR_NG_HPP
#define _EXPARX_RSI_MONITOR_NG_HPP

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
#include <extras_rsi/remote/monitors/File.hpp>
#include <extras_rsi/remote/ParametersX.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief
         *
         */
        concrete class NgMonitor extends FileMonitor
            with ParametersInterface {

            Pathname _srcDir;
            Parameter _rsiIP;
            ParametersX _paraneters;

        public:

            /**
             * @brief CausalityInterface
             *
             */
            virtual void effect() override;
            virtual void reset() override;

            /**
             * @brief ParametersInterface
             *
             */
            virtual void parse(int argc, char const* argv[]) override;

            virtual Parameter parameters() const override
            {
                return _paraneters.parameters();
            }
            virtual const Parameter& address() const override
            {
                return _paraneters.address();
            }
            virtual const Parameter& port() const override
            {
                return _paraneters.port();
            }
            virtual const Filenames& filenames() const override
            {
                return _paraneters.filenames();
            }
            virtual ParameterList list() const override
            {
                return _paraneters.list();
            }

        };


    }
}

#endif // _EXPARX_RSI_MONITOR_NG_HPP


