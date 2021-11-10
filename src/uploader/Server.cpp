#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <rsi/sockets/Types.hpp>
#include <rsi/sockets/Client.hpp>
#include <rsi/sockets/RequestType.hpp>
#include <rsi/uploader/Uploader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


using namespace std;

namespace extras {

    /**
     * @brief concrete class UploaderServer
     *
     *   build/rsi_client 127.0.0.1 8080 transfer send.txt
     *   ss >> prg >> filename >> ip >> port;
     *
     */
    void rsi::UploaderServer::connect() {
        this->_sockfd = extras::rsi::configure_serversocket(
            ip().c_str(), stoi(port()), _server_addr);
        socklen_t addr_size = sizeof(_new_addr);
        this->_new_sock =
            accept(this->_sockfd, (struct sockaddr*)&_new_addr, &addr_size);
        if (_new_sock == -1) {
            ::close(this->_sockfd);
            throw RSIException("Timeout on uploader_server accept", __INFO__);
        }
    }

    void rsi::UploaderServer::transfer() const {
        auto uploaded_file =
            extras::replace_all(filename(), ".txt", "_uploaded.txt");
        extras::rsi::write_file(uploaded_file.c_str(), this->_new_sock);
        system("ls -la");
        /**
         * @brief Right here, Right now...
         *
         */
        system("ls send* -la");
        auto delete_cmd = "rm send.txt";
        system(delete_cmd);
        system("ls send* -la");
        auto copy_cmd = "mv " + uploaded_file + " send.txt";
        system(copy_cmd.c_str());
        auto cat_cmd = "cat send.txt";
        system(cat_cmd);
        system("ls send* -la");
    }

    void rsi::DownloaderServer::transfer() const {
        extras::rsi::send_file2(filename().c_str(), this->_new_sock);
    }

    void rsi::UploaderServer::close() const {
        ::close(this->_new_sock);
        ::close(this->_sockfd);
    }

}  // namespace extras