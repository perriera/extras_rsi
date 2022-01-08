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

    }  // namespace rsi
}  // namespace extras
