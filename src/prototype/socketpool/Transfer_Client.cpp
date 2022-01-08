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
#include <extras_rsi/prototype/requests/RequestType.hpp>
#include <extras_rsi/remote/sockets/SubSystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/filesystem/system.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief SocketPoolClient::transfer()
         *
         */
        void SocketPoolClient::transfer() {
            try {
                std::string msg = *this;
                send_line_block(msg);
                RequestTypeCompilation compilation(this->_client_socket);
                compilation.read_line_block();
                auto list = compilation.compilation();
                for (auto item : clients(list)) {
                    // cout << "msg received: " << item << endl;
                    auto cmd = item;
                    system(cmd.c_str());
                }
                // std::string cmd = "ls -la " + filename();
                // extras::SystemException::assertion(cmd, __INFO__);
                std::cout << std::endl;
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
        }

    }  // namespace rsi
}  // namespace extras
