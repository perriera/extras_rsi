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
 * The above copyright notice and  this permission  notice shall be
 * included in all copies or  substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESSED  OR   IMPLIED,  INCLUDING   BUT  NOT  LIMITED  TO  THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT.  IN  NO  EVENT  SHALL EXPARX  INCORPORATED
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER  IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM, OUT  OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR  OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Except  as  contained  in this  notice, the  name of  the EXPARX
 * INCORPORATED shall not  be used in  advertising or  otherwise to
 * promote the sale, use or other dealings in this Software without
 * prior written authorization from EXPARX INCORPORATED.
 *
 * exparx.com and www.exparx.com  are domain names  registered with
 * EXPARX INCORPORATED, (other GPL-themed licenses are included).
 *
 */

#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/sockets/Client.hpp>
#include <rsi/sockets/Server.hpp>
#include <rsi/sockets/RequestType.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        void SocketPoolServer::transfer() const {
            try {
                string msg;
                while (msg.size() == 0) msg = read_line(this->_client_socket);
                if (msg.size() == 0) throw std::string("test exception");
                SocketPoolClient client(msg, _compilerInterface);
                // cout << "msg received: " << client << endl;
                RequestTypeCompiler compiler;
                auto compilation = compiler.compile(client);
                compilation.writeSocket(this->_client_socket);
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
         * @brief concrete class SocketPoolServer
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */
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

    }  // namespace rsi
}  // namespace extras
