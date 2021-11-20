#include <rsi/uploader/Uploader.hpp>
#include <rsi/uploader/Downloader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/filesystem/paths.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <iostream>
#include <filesystem>
#include <extras/status/StatusLine.hpp>

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
        std::cout << extras::pass(parcel.packed()) << std::endl;
        std::cout << extras::pass(" uploaded") << std::endl;
    }

    void rsi::UploaderServer::transfer() const {

        rsi::Parameter parameter = filename();
        rsi::Parcel parcel(parameter);
        extras::rsi::write_file(parcel.packed(), this->_new_sock);
        std::cout << extras::pass(parcel.packed()) << std::endl;
        std::cout << extras::pass(" uploaded") << std::endl;
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
        std::cout << extras::pass(parcel.packed()) << std::endl;
        std::cout << extras::pass(" downloaded") << std::endl;
    }

    void rsi::DownloaderServer::transfer() const {
        rsi::Parameter parameter = ~extras::Paths(filename());
        rsi::Parcel parcel(parameter);
        parcel.pack();
        extras::rsi::send_file2(parcel.packed(), this->_new_sock);
        std::cout << extras::pass(parcel.packed()) << std::endl;
        std::cout << extras::pass(" downloaded") << std::endl;
    }



}  // namespace extras
