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

#include <extras_rsi/socketpool/Client.hpp>
#include <extras_rsi/socketpool/Server.hpp>
#include <extras_rsi/requests/RequestTypeFour.hpp>
#include <extras_rsi/subsystem.hpp>
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

        Parameters SocketPoolServer::parameters(int argc, char const* argv[]) {
            char const* extra_argv[] = { argv[0], argv[1], argv[2], "ignore.txt" };
            return _socketParaneters.parameters(++argc, extra_argv);
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
         * @brief SocketPoolServer::transfer()
         *
         */
        void SocketPoolServer::transfer() {
            try {
                string msg;
                while (msg.size() == 0) msg = read_line_block();
                if (msg.size() == 0) throw std::string("test exception");
                SocketPoolClient client(msg, _compilerInterface);
                // cout << "msg received: " << client << endl;
                RequestTypeCompilerTypeFour compiler(*this, this->_client_socket);
                auto compilation = compiler.compile(client, PortAuthority::instance());
                compilation.send_line_block("");
                auto list = compilation.compilation();
                for (auto item : servers(list)) {
                    // cout << "msg received: " << item << endl;
                    auto cmd = item + " &";
                    system(cmd.c_str());
                }
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
                send_line(ex.what(), this->_client_socket);
            }
            catch (...) {
                send_line("Unknown exception thrown", this->_client_socket);
            }
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
