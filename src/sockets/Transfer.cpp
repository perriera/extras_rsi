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
         * @brief SocketPoolClient::transfer()
         *
         */
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

        /**
         * @brief SocketPoolServer::transfer()
         *
         */
        void SocketPoolServer::transfer() const {
            try {
                string msg;
                while (msg.size() == 0) msg = read_line(this->_client_socket);
                if (msg.size() == 0) throw std::string("test exception");
                SocketPoolClient client(msg);
                cout << "msg received: " << client << endl;
                RequestTypeCompiler compiler;
                auto compilation = compiler.compile(client);
                compilation.writeSocket(this->_client_socket);
                auto list = compilation.compilation();
                for (auto item : servers(list)) {
                    cout << "msg received: " << item << endl;
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
