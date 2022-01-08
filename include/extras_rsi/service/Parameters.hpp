/**
 * @file Parameters.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief ParametersInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSIUPLOADERPARAMETERS_HPP
#define _EXPARX_RSIUPLOADERPARAMETERS_HPP

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

namespace extras {
    namespace rsi {
        namespace uploader {

            /**
             * @brief ParametersInterface
             *
             */

            interface ParametersInterface {

                virtual Parameters parameters(int argc, char const* argv[]) pure;
                virtual  Parameter program() const pure;
                virtual  Parameter ip() const pure;
                virtual  Parameter port() const pure;
                virtual  Parameter filename() const pure;
                virtual  Parameters extra_files() const pure;

            };

        }
    }
}

#endif // _EXPARX_RSISOCKETSPARAMETERS_HPP


