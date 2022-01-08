/**
 * @file RequestType.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief RequestTypeCompilerTypeThree
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSIREQUESTTYPEFOUR_HPP
#define _EXPARX_RSIREQUESTTYPEFOUR_HPP

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
#include <extras_rsi/prototype/requests/RequestTypeBase.hpp>
#include <iostream>

  /**
   * @brief
   *
   */

namespace extras {
    namespace rsi {

        /**
         * @brief RequestTypeCompilerTypeThree
         *
         */
        concrete class RequestTypeCompilerTypeFour extends RequestTypeCompilerBase {
        public:
            RequestTypeCompilerTypeFour(
                const ServiceTypeCompilerInterface& compilerInterface, int socket)
                : RequestTypeCompilerBase(compilerInterface, socket) {}

            virtual RequestTypeCompilation compile(
                const rsi::sockets::ParametersInterface& client,
                PortAuthorityInterface& portAuthority) const override;

        };
    }
}

#endif // _EXPARX_RSIREQUESTTYPEFOUR_HPP

