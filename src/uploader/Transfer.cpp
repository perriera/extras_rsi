#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/uploader/Uploader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     * @brief concrete class UploaderClient
     *
     *   build/rsi_client 127.0.0.1 8080 transfer send.txt
     *   ss >> prg >> filename >> ip >> port;
     *
     */

    void rsi::UploaderClient::transfer() {
        extras::rsi::send_file2(payload().c_str(), this->_sockfd);
    }

    void rsi::DownloaderClient::transfer() {
        extras::rsi::write_file(payload_downloaded().c_str(), this->_sockfd);
    }

    void rsi::UploaderServer::transfer() {
        extras::rsi::write_file(payload_uploaded().c_str(), this->_new_sock);
    }

    void rsi::DownloaderServer::transfer() {
        extras::rsi::send_file2(payload().c_str(), this->_new_sock);
    }

}  // namespace extras
