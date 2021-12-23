/**
 * @file RequestType.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief RequestTypeCompilationInterface, RequestTypeCompilerInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSIREQUESTTYPEBASE_HPP
#define _EXPARX_RSIREQUESTTYPEBASE_HPP

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
#include <extras_rsi/requests/RequestType.hpp>
#include <iostream>

  /**
   * @brief
   *
   */

namespace extras {
    namespace rsi {

        /**
         * @brief RequestTypeCompilerInterface
         *
         */

        interface RequestTypeCompilerInterface {
            virtual RequestTypeCompilation compile(
                const rsi::sockets::ParametersInterface& client,
                PortAuthorityInterface& portAuthority) const pure;
        };

        /**
         * @brief RequestTypeCompilerTypeOne
         *
         */
        abstract class RequestTypeCompilerBase implements RequestTypeCompilerInterface
            with ServiceTypeCompilerInterface {
            const ServiceTypeCompilerInterface& _compilerInterface;
        protected:
            int _socket = -1;
        public:
            RequestTypeCompilerBase(const ServiceTypeCompilerInterface& compilerInterface, int socket)
                : _compilerInterface(compilerInterface), _socket(socket) {}

            virtual ServiceTypeList common(ServiceTypeMap& map,
                const RequestTypeList& requests) const override {
                return _compilerInterface.common(map, requests);
            }

            virtual ServiceTypeList clients(
                const RequestTypeList& requests) const override {
                return _compilerInterface.clients(requests);
            }

            virtual ServiceTypeList servers(
                const RequestTypeList& requests) const override {
                return _compilerInterface.servers(requests);
            }

            virtual bool isParameter(const RequestType& requestType) const override {
                return _compilerInterface.isParameter(requestType);
            }

        };



    }
}

#endif // _EXPARX_RSIREQUESTTYPEBASE_HPP


