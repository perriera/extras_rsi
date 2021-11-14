#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/uploader/Uploader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <extras/filesystem/paths.hpp>
#include <rsi/parcel/Parcel.hpp>
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
        rsi::Parameter parcel = ~extras::Paths(filename());
        rsi::Parcel packed(parcel);
        packed.pack();
        extras::rsi::send_file2(packed.packed().c_str(), this->_sockfd);
    }

    /**
     * @brief UploaderServer::transfer()
     *
     */
    void rsi::UploaderServer::transfer() const {
        rsi::Parameter parcel = ~extras::Paths(filename());
        rsi::Parcel packed(parcel);
        std::string uploaded_file = packed.packed();
        extras::rsi::write_file(uploaded_file.c_str(), this->_new_sock);
        packed.unpack();
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
        rsi::Parameter parcel = ~extras::Paths(filename());
        rsi::Parcel packed(parcel);
        std::string downloaded_file = packed.packed();
        extras::rsi::write_file(downloaded_file.c_str(), this->_sockfd);
        packed.unpack();
    }

    /**
     * @brief DownloaderServer::transfer()
     *
     */
    void rsi::DownloaderServer::transfer() const {
        rsi::Parameter parcel = ~extras::Paths(filename());
        rsi::Parcel packed(parcel);
        packed.pack();
        std::string downloaded_file = packed.packed();
        extras::rsi::send_file2(downloaded_file.c_str(), this->_new_sock);
    }

}  // namespace extras
