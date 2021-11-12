#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/uploader/Uploader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>

using namespace std;

namespace extras {

    /**
     * @brief concrete class UploaderClient
     *
     *   build/rsi_client 127.0.0.1 8080 transfer send.txt
     *   ss >> prg >> filename >> ip >> port;
     *
     */
    void rsi::UploaderClient::connect() {
        this->_sockfd = extras::rsi::connect_to_server(ip().c_str(), stoi(port()),
            _server_addr);
    }

    void rsi::UploaderClient::transfer() {
        extras::rsi::send_file2(payload().c_str(), this->_sockfd);
    }

    void rsi::DownloaderClient::transfer() {
        extras::rsi::write_file(payload_downloaded().c_str(), this->_sockfd);
    }

    void rsi::UploaderClient::close() { ::close(this->_sockfd); }

}  // namespace extras
