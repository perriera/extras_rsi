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

#ifndef _EXPARX_RSI_CLIENTSERVER_HPP
#define _EXPARX_RSI_CLIENTSERVER_HPP

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
#include <extras_rsi/remote/ClientServerInterface.hpp>
#include <extras_rsi/remote/Invocation.hpp>

#include <extras_rsi/exceptions.hpp>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

namespace extras {
    namespace rsi {

        /**
         * @brief InvocationClient
         *
         */
        concrete class InvocationClient extends rsi::Invocation
            with rsi::ClientInterface {

            struct sockaddr_in _client_addr;
            bool _timeout = true;

        public:

            InvocationClient(rsi::VendorInterface& vendor, bool timeout = true)
                : Invocation(vendor), _timeout(timeout) {};

            virtual void connect() override;
            virtual void close() const override;
            virtual void send() override;

        };

        /**
         * @brief InvocationServer
         *
         */
        concrete class InvocationServer extends rsi::Invocation
            with rsi::ServerInterface {

            struct sockaddr_in _server_addr;
            struct sockaddr_in _client_addr;
            int _server_socket;
            bool _timeout = true;

        public:

            InvocationServer(rsi::VendorInterface& vendor, bool timeout = true)
                : Invocation(vendor), _timeout(timeout) {};

            virtual void connect() override;
            virtual void accept() override;
            virtual void close() const override;
            virtual void receive() override;

        };



    }
}

#endif // _EXPARX_RSI_CLIENTSERVER_HPP


