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
