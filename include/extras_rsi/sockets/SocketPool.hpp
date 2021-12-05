/**
 * @file SocketPool.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief SocketPoolInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISOCKETSPOOL_HPP
#define _EXPARX_RSISOCKETSPOOL_HPP

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
#include <extras/strings.hpp>
#include <extras_rsi/sockets/Parameters.hpp>
#include <extras_rsi/sockets/LineBlock.hpp>
#include <extras_rsi/sockets/ServiceType.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief SocketPoolInterface
         *
         * The idea is that we assign a port to be the authority on deligating
         * available port numbers, (from a range of port numbers). At the basic
         * level a series of predefined tokens are given to this interface. If all
         * tokens are reconized then a port number is returned for each token.
         *
         * The purpose of a token is to inform the SocketPool instance what type of
         * socket service will be expected to be running on that port. Earlier
         * prototypes to this just returned a single port number. However, it was
         * soon realized that perhaps more than one port is required and to inform
         * the socket pool manager in advance of what type of service to running on
         * that port would be advantageous.
         *
         * This version only returns a port number, a more enhanced version would
         * support IP addresses, (hence supporting socket pools over different IPs).
         *
         */

        interface SocketPoolInterface {
            virtual void transfer() pure;
        };

        /**
         * @brief class SocketPool
         *
         */
        abstract class SocketPool implements SocketPoolInterface with
            sockets::ParametersInterface with ServiceTypeCompilerInterface
            with LineBlockInterface {
        protected:

            SocketParaneters _socketParaneters;
            SocketRequestTypeList _types;
            SocketRequestTypeMap _lastRequest;
            const ServiceTypeCompilerInterface& _compilerInterface;

        public:

            SocketPool(const ServiceTypeCompilerInterface& compilerInterface)
                :_compilerInterface(compilerInterface) {}

            virtual Parameters parameters(int argc, char const* argv[]) override {
                return _socketParaneters.parameters(argc, argv);
            }
            virtual  Parameter program() const override { return _socketParaneters.program(); }
            virtual  Parameter ip() const override { return _socketParaneters.ip(); }
            virtual  Parameter port() const override { return _socketParaneters.port(); }
            virtual  Parameter filename() const override { return _socketParaneters.filename(); }
            virtual  SocketRequestTypeList requests() const override {
                return _socketParaneters.requests();
            }

            virtual ServiceTypeList clients(
                const RequestTypeList& requests) const override {
                return _compilerInterface.clients(requests);
            }
            virtual ServiceTypeList servers(
                const RequestTypeList& requests) const override {
                return _compilerInterface.servers(requests);
            }
        };


    }
}

#endif // _EXPARX_RSISOCKETSPOOL_HPP


