/**
 * @file ParametersInterface.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief ParametersInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSI_PARAMETERSINTERFACE_HPP
#define _EXPARX_RSI_PARAMETERSINTERFACE_HPP

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
#include <extras_rsi/remote/ServiceInterface.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief ParametersInterface
         *
         */
        interface ParametersInterface {

            /**
             * @brief parse()
             * @note parse recognized parameters
             *
             * @param argc
             * @param argv
             */
            virtual void parse(int argc, char const* argv[]) pure;
            virtual Parameter parameters() const pure;

            virtual const Parameter& address() const pure;
            virtual const Parameter& port() const pure;
            virtual const Filenames& filenames() const pure;
            virtual ParameterList list() const pure;

        };


    }
}

#endif // _EXPARX_RSI_PARAMETERSINTERFACE_HPP


