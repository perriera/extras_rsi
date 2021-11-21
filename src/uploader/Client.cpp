#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/uploader/Uploader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

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

    void rsi::UploaderClient::close() const { ::close(this->_sockfd); }

    void rsi::UploaderClient::send(const Filename& filename) const {
        //         ifstream in(filename);
        // rsi::BinFile binFile = rsi::ConvertFile().loadBin(in);
        // internet = binFile;
        extras::rsi::send_file2(filename, this->_sockfd);
    }

    rsi::Filename rsi::UploaderClient::write(const Filename& filename) const {
        extras::rsi::write_file(filename, this->_sockfd);
        return filename;
    }

}  // namespace extras
