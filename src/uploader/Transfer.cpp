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

#include <chrono>
#include <thread>

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
        packed.unpack();
        packed.unzip();
        cout << "sending " << packed.packed() << endl;
        extras::rsi::send_file2(packed.packed().c_str(), this->_sockfd);
    }

    /**
     * @brief UploaderServer::transfer()
     *
     */
    void rsi::UploaderServer::transfer() const {

        rsi::Parameter parameter = filename();
        rsi::Parcel parcel(parameter);
        extras::rsi::write_file(parcel.packed().c_str(), this->_new_sock);
        cout << parcel.packed() << " written" << endl;

    }

    void rsi::VendorClient::transfer() const {
    }

    void rsi::VendorServer::transfer() const {
        rsi::Parameter parameter = ~extras::Paths(filename());
        rsi::Parcel parcel(parameter);
        parcel.unpack();
        parcel.unzip();
        parcel.dir();
        parcel.cat();
        parcel.pack();
        parcel.dir();
    }

    /**
     * @brief DownloaderClient::transfer()
     *
     */
    void rsi::DownloaderClient::transfer() const {
        rsi::Parameter parameter = ~extras::Paths(filename());
        rsi::Parcel parcel(parameter);
        extras::rsi::write_file(parcel.packed().c_str(), this->_sockfd);
        parcel.unpack();
        parcel.cat();
        parcel.unzip();
        parcel.dir();
    }

    /**
     * @brief DownloaderServer::transfer()
     *
     */
    void rsi::DownloaderServer::transfer() const {
        rsi::Parameter parameter = ~extras::Paths(filename());
        rsi::Parcel parcel(parameter);
        parcel.pack();
        extras::rsi::send_file2(parcel.packed().c_str(), this->_new_sock);
        // parcel.clean();
        // parcel.dir();
    }

}  // namespace extras
