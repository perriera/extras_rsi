#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/uploader/Uploader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <filesystem>
#include <extras/filesystem/system.hpp>

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

    void rsi::UploaderServer::close() const {
        ::close(this->_new_sock);
        ::close(this->_sockfd);
    }

    void rsi::UploaderServer::send(const Filename& filename) const {
        extras::rsi::send_file2(filename, this->_new_sock);
    }

    void rsi::UploaderServer::send_line(const rsi::UploaderStatus& msg) const {
        extras::rsi::send_line(msg, this->_new_sock);
    }

    rsi::UploaderStatus rsi::UploaderServer::read_line() const {
        return extras::rsi::read_line(this->_new_sock);
    }

    rsi::Filename rsi::UploaderServer::write(const Filename& filename) const {
        if (!fs::exists(server_dir))
            SystemException::assertion("mkdir " + server_dir, __INFO__);
        auto target = extras::replace_all(filename, "data/", server_dir);
        extras::rsi::write_file(target, this->_new_sock);
        return target;
    }

}  // namespace extras
