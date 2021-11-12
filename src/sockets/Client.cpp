#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/sockets/Client.hpp>
#include <rsi/sockets/RequestType.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
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

    }  // namespace rsi
}  // namespace extras
