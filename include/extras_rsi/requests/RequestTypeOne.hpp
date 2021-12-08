/**
 * @file RequestType.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief RequestTypeCompilerTypeOne
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSIREQUESTTYPEONE_HPP
#define _EXPARX_RSIREQUESTTYPEONE_HPP

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
#include <extras_rsi/requests/RequestTypeBase.hpp>
#include <iostream>

  /**
   * @brief
   *
   */

namespace extras {
    namespace rsi {

        /**
         * @brief RequestTypeCompilerTypeOne
         *
         */
        concrete class RequestTypeCompilerTypeOne implements RequestTypeCompilerInterface {
            int _socket = -1;
        public:
            RequestTypeCompilerTypeOne(int socket) : _socket(socket) {}

            virtual RequestTypeCompilation compile(
                const rsi::sockets::ParametersInterface& client,
                PortAuthorityInterface& portAuthority) const override;

            virtual RequestTypeCompilation compile(
                const rsi::sockets::ParametersInterface& client) const {
                return compile(client, PortAuthority::instance());
            }
        };


    }
}

#endif // _EXPARX_RSIREQUESTTYPEONE_HPP


