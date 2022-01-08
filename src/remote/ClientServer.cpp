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

#include <arpa/inet.h>
#include <unistd.h>
#include <extras_rsi/sockets/SubSystem.hpp>
#include <extras_rsi/remote/ClientServer.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief InvocationClient
         *
         */
        void InvocationClient::connect() {
            _client_socket = rsi::connect_to_server(
                address().c_str(),
                stoi(port()),
                _client_addr, _timeout);
            if (_client_socket == -1) {
                // TODO:: write a proper assertion() for this
                ::close(_client_socket);
                throw RSIException("InvocationClient::connect() issue", __INFO__);
            }
        }

        void InvocationClient::close() const {
            ::close(this->_client_socket);
        }

        void InvocationClient::send() {
            invoke(_client_socket);
        }

        /**
         * @brief InvocationServer
         *
         */
        void InvocationServer::connect() {
            _server_socket = rsi::configure_serversocket(
                address().c_str(),
                stoi(port()),
                _server_addr, _timeout);
            if (_server_socket == -1) {
                // TODO:: write a proper assertion() for this
                ::close(_server_socket);
                throw RSIException("InvocationServer::connect() issue", __INFO__);
            }
        }

        void InvocationServer::accept() {
            socklen_t addr_size = sizeof(_client_addr);
            _client_socket = ::accept(_server_socket, (struct sockaddr*)&_client_addr, &addr_size);
            if (_client_socket == -1) {
                // TODO:: write a proper assertion() for this
                ::close(_client_socket);
                throw RSIException("InvocationServer::accept() issue", __INFO__);
            }
        }
        void InvocationServer::close() const {
            ::close(this->_client_socket);
            ::close(this->_server_socket);
        }

        void InvocationServer::receive() {
            service(_client_socket);
        }

    }  // namespace rsi
}  // namespace extras
