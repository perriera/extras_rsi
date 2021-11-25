#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/sockets/Client.hpp>
#include <rsi/sockets/RequestType.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
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

        void SocketPoolClient::transfer() const {
            try {
                std::string msg = *this;
                send_line(msg, this->_client_socket);
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


    }  // namespace rsi
}  // namespace extras
