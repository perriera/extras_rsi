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

#include <extras_rsi/sockets/Client.hpp>
#include <extras_rsi/sockets/RequestType.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/filesystem/system.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief concrete class SocketPoolClient
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */
        void SocketPoolClient::connect() {
            this->_client_socket =
                connect_to_server(ip().c_str(), stoi(port()), _server_addr);
        }

        void SocketPoolClient::close() const { ::close(this->_client_socket); }

        /**
         * @brief SocketPoolClient::transfer()
         *
         */
        void SocketPoolClient::transfer() const {
            try {
                std::string msg = *this;
                send_line_block(msg);
                RequestTypeCompilation compilation;
                compilation.readSocket(this->_client_socket);
                auto list = compilation.compilation();
                for (auto item : clients(list)) {
                    // cout << "msg received: " << item << endl;
                    auto cmd = item;
                    system(cmd.c_str());
                }
                std::string cmd = "ls -la " + filename();
                extras::SystemException::assertion(cmd, __INFO__);
                std::cout << std::endl;
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
        }

        /**
         * @brief send_line_block()
         *
         * @param msg
         */
        void  SocketPoolClient::send_line_block(const rsi::LinePacket& msg) const {
            extras::rsi::send_line(msg, this->_client_socket);
        }

        /**
         * @brief read_line_block()
         *
         * @return LinePacket
         */
        LinePacket  SocketPoolClient::read_line_block() const {
            return extras::rsi::read_line(this->_client_socket);
        }

    }  // namespace rsi
}  // namespace extras
