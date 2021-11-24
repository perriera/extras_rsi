#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/uploader/Uploader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <filesystem>
#include <extras/filesystem/system.hpp>

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

    void rsi::UploaderClient::send_line(const rsi::UploaderStatus& msg) const {
        extras::rsi::send_line(msg, this->_sockfd);
    }

    rsi::UploaderStatus rsi::UploaderClient::read_line() const {
        return extras::rsi::read_line(this->_sockfd);
    }

    rsi::Filename rsi::UploaderClient::write(const Filename& filename) const {
        static std::string client_dir = "data/client/";

        if (fs::exists(client_dir)) {
            fs::remove_all(client_dir);
            SystemException::assertion("mkdir " + client_dir, __INFO__);
        }
        // if (internet.size() == 0)
        //     throw "Nothing to save";
        auto target = extras::replace_all(filename, "data/", client_dir);
        // ofstream out(target);
        // rsi::ConvertFile().saveBin(out, internet);
        // internet.clear();
        // return target;

        extras::rsi::write_file(target, this->_sockfd);
        return target;
    }

}  // namespace extras
