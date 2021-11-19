#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/uploader/Uploader.hpp>
#include <rsi/uploader/Downloader.hpp>
#include <rsi/uploader/Vendor.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/filesystem/paths.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <iostream>
#include <filesystem>
#include <rsi/sockets/StatusLine.hpp>

#include <chrono>
#include <thread>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     * @brief Uploader Client/Server ::transfer()
     *
     */
    void rsi::UploaderClient::transfer() const {

        rsi::Parameter parameter = ~extras::Paths(filename());
        rsi::Parcel parcel(parameter);
        parcel.pack();
        // packed.unpack();
        // packed.unzip();
        extras::rsi::send_file2(parcel.packed(), this->_sockfd);
        std::cout << rsi::pass(parcel.packed()) << std::endl;
        std::cout << rsi::pass(" uploaded") << std::endl;
    }

    void rsi::UploaderServer::transfer() const {

        rsi::Parameter parameter = filename();
        rsi::Parcel parcel(parameter);
        extras::rsi::write_file(parcel.packed(), this->_new_sock);
        std::cout << rsi::pass(parcel.packed()) << std::endl;
        std::cout << rsi::pass(" uploaded") << std::endl;
    }

    /**
     * @brief Vendor Client/Server ::transfer()
     *
     */
    void rsi::DownloaderClient::transfer() const {
        rsi::Parameter parameter = ~extras::Paths(filename());
        rsi::Parcel parcel(parameter);
        extras::rsi::write_file(parcel.packed(), this->_sockfd);
        parcel.unpack();
        // parcel.cat();
        // parcel.unzip();
        parcel.dir();
        std::cout << rsi::pass(parcel.packed()) << std::endl;
        std::cout << rsi::pass(" downloaded") << std::endl;
    }

    void rsi::DownloaderServer::transfer() const {
        rsi::Parameter parameter = ~extras::Paths(filename());
        rsi::Parcel parcel(parameter);
        parcel.pack();
        extras::rsi::send_file2(parcel.packed(), this->_new_sock);
        std::cout << rsi::pass(parcel.packed()) << std::endl;
        std::cout << rsi::pass(" downloaded") << std::endl;
    }

    /**
     *  @brief Vendor Client/Server ::transfer()
     *
     */
    void rsi::VendorClient::transfer() const {
        std::cout << rsi::pass(filename()) << std::endl;
        std::cout << rsi::pass(" processed") << std::endl;
    }

    void rsi::VendorServer::transfer() const {
        rsi::Parameter parameter = ~extras::Paths(filename());
        rsi::Parcel parcel(parameter);
        // parcel.unpack();
        // parcel.unzip();
        // parcel.dir();
        // parcel.cat();
        // parcel.pack();
        // parcel.dir();
        std::cout << extras::cyan;
        parcel.unzip();
        std::cout << rsi::pass(filename()) << std::endl;
        std::cout << rsi::pass(" processed") << std::endl;
    }


}  // namespace extras
