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
        auto uploaded_file =
            extras::replace_all(filename(), ".txt", "_uploaded.txt");
        extras::rsi::write_file(uploaded_file.c_str(), this->_new_sock);
        system("ls -la");
        /**
         * @brief Right here, Right now...
         *
         */
         // system("ls send* -la");
         // auto delete_cmd = "rm send.txt";
         // system(delete_cmd);
         // system("ls send* -la");
         // auto copy_cmd = "mv " + uploaded_file + " send.txt";
         // system(copy_cmd.c_str());
         // auto cat_cmd = "cat send.txt";
         // system(cat_cmd);
         // system("ls send* -la");
    }

    void rsi::DownloaderServer::transfer() {
        extras::rsi::send_file2(filename().c_str(), this->_new_sock);
        fs::remove(filename());
    }

    void rsi::UploaderServer::close() {
        ::close(this->_new_sock);
        ::close(this->_sockfd);
    }

}  // namespace extras
