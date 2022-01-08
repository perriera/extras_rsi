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

#include <extras_rsi/prototype/socketpool/Client.hpp>
#include <extras_rsi/prototype/socketpool/Server.hpp>
#include <extras_rsi/prototype/requests/RequestTypeFour.hpp>
#include <extras_rsi/remote/sockets/SubSystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief concrete class SocketPoolServer
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */

        PortAuthority SocketPoolServer::configPortAuthority(
            const Parameter& server_port,
            const Parameter& range) {
            int port = std::stoi(server_port);
            BadRangeFormatException::assertion(range, __INFO__);
            auto parts = extras::split(range, '-');
            int from = std::stoi(parts[0]);
            int to = std::stoi(parts[1]);
            int span = to - from;
            return PortAuthority(port, from, span);
        }

        Parameters SocketPoolServer::parameters(int argc, char const* argv[]) {
            auto parameters = _socketParaneters.parameters(argc, argv);
            _PortAuthority = configPortAuthority(this->port(), this->filename());
            return parameters;
        }

        void SocketPoolServer::connect() {
            this->_server_socket = configure_serversocket(ip().c_str(), stoi(port()),
                _server_addr, false);
            if (this->_server_socket == -1) {
                ::close(this->_server_socket);
                throw RSIException("Timeout on uploader_server connect", __INFO__);
            }
        }

        void SocketPoolServer::accept() {
            socklen_t addr_size = sizeof(_new_addr);
            this->_client_socket = ::accept(
                this->_server_socket, (struct sockaddr*)&_new_addr, &addr_size);
            if (_client_socket == -1) {
                ::close(this->_server_socket);
                throw RSIException("Timeout on uploader_server accept", __INFO__);
            }
        }

        void SocketPoolServer::close() const {
            ::close(this->_client_socket);
            ::close(this->_server_socket);
        }

        /**
         * @brief send_line_block()
         *
         * @param msg
         */
        void  SocketPoolServer::send_line_block(const rsi::LinePacket& msg) const {
            extras::rsi::send_line(msg, this->_client_socket);
        }

        /**
         * @brief read_line_block()
         *
         * @return LinePacket
         */
        LinePacket  SocketPoolServer::read_line_block() {
            return extras::rsi::read_line(this->_client_socket);
        }

    }  // namespace rsi
}  // namespace extras
