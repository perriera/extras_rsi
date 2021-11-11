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

    void rsi::UploaderServer::transfer() {
        extras::rsi::write_file(parcel_uploaded().c_str(), this->_new_sock);
        system("ls -la");
        /**
         * @brief Right here, Right now...
         *
         */
    }

    void rsi::DownloaderServer::transfer() {
        extras::rsi::send_file2(parcel().c_str(), this->_new_sock);
        fs::remove(parcel());
    }

    void rsi::UploaderServer::close() {
        ::close(this->_new_sock);
        ::close(this->_sockfd);
    }

}  // namespace extras
