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
