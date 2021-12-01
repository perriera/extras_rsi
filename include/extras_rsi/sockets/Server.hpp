/**
 * @file Server.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief SocketPoolServerInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISOCKETSSERVER_HPP
#define _EXPARX_RSISOCKETSSERVER_HPP

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
#include <extras_rsi/sockets/SocketPool.hpp>
#include <extras_rsi/sockets/PortAuthority.hpp>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {

        /**
         * @brief SocketPoolServerInterface
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

        interface SocketPoolServerInterface {
            virtual void connect() pure;
            virtual void accept() pure;
            virtual void close() const pure;
            virtual PortAuthority& portAuthority() pure;
        };

        /**
         * @brief SocketPoolServer
         *
         */
        concrete class SocketPoolServer extends SocketPool with
            SocketPoolServerInterface {
            struct sockaddr_in _server_addr;
            struct sockaddr_in _new_addr;
            int _server_socket;
            int _client_socket;
            PortAuthority _PortAuthority;

        public:
            SocketPoolServer(const ServiceTypeCompilerInterface& compiler) : SocketPool(compiler) {};
            virtual PortAuthority& portAuthority() override { return _PortAuthority; }
            virtual void connect() override;
            virtual void accept() override;
            virtual void close() const override;
            virtual void transfer() const override;

        };

    }
}

#endif // _EXPARX_RSISOCKETSSERVER_HPP


