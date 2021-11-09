#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <rsi/sockets/Types.hpp>
#include <rsi/sockets/Client.hpp>
#include <rsi/sockets/RequestType.hpp>
#include <rsi/sockets/PortAuthority.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// virtual const Parameter &program() const pure;
// virtual const Parameter &ip() const pure;
// virtual const Parameter &port() const pure;
// virtual const Parameter &filename() const pure;
// virtual const SocketRequestTypeList &requests() const pure;

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

        void SocketPoolClient::transfer() const {
            try {
                std::string msg = *this;
                send_line(msg, this->_client_socket);
                RequestTypeCompilation compilation;
                compilation.readSocket(this->_client_socket);
                auto list = compilation.compilation();
                for (auto item : clients(list)) {
                    cout << "msg received: " << item << endl;
                    auto cmd = item;
                    system(cmd.c_str());
                }
                system("ls -la");
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
        }


    }  // namespace rsi
}  // namespace extras
