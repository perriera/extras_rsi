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
     * @brief UploaderClient::transfer()
     *
     */
    void rsi::UploaderClient::transfer() const {
        extras::rsi::send_file2(filename().c_str(), this->_sockfd);
    }

    /**
     * @brief UploaderServer::transfer()
     *
     */
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

    /**
     * @brief DownloaderClient::transfer()
     *
     */
    void rsi::DownloaderClient::transfer() const {
        auto downloaded_file =
            extras::replace_all(filename(), ".txt", "_downloaded.txt");
        extras::rsi::write_file(downloaded_file.c_str(), this->_sockfd);
    }

    /**
     * @brief DownloaderServer::transfer()
     *
     */
    void rsi::DownloaderServer::transfer() const {
        extras::rsi::send_file2(filename().c_str(), this->_new_sock);
    }

}  // namespace extras
