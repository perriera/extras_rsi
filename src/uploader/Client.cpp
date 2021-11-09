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

namespace exparx {

    /**
     * @brief concrete class UploaderClient
     *
     *   build/rsi_client 127.0.0.1 8080 transfer send.txt
     *   ss >> prg >> filename >> ip >> port;
     *
     */
    void rsi::UploaderClient::connect() {
        this->_sockfd = exparx::rsi::connect_to_server(ip().c_str(), stoi(port()),
            _server_addr);
    }

    void rsi::UploaderClient::transfer() const {
        exparx::rsi::send_file2(filename().c_str(), this->_sockfd);
    }

    void rsi::DownloaderClient::transfer() const {
        auto downloaded_file =
            extras::replace_all(filename(), ".txt", "_downloaded.txt");
        exparx::rsi::write_file(downloaded_file.c_str(), this->_sockfd);
    }

    void rsi::UploaderClient::close() const { ::close(this->_sockfd); }

}  // namespace extras
