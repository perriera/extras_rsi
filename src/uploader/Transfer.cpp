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
#include <rsi/parcel/ParcelImploder.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     * @brief Uploader Client/Server ::transfer()
     *
     */
    void rsi::UploaderClient::transfer() const {
        rsi::Parameter parameter = ~extras::Paths(filename());
        rsi::ParcelImploder parcelImploder;
        auto wrapped = parcelImploder.wrap(filename());
        extras::rsi::send_file2(wrapped, this->_sockfd);
        std::cout << extras::pass(wrapped) << std::endl;
        std::cout << extras::pass(" uploaded") << std::endl;
    }

    void rsi::UploaderServer::transfer() const {
        rsi::ParcelImploder parcelImploder;
        parcelImploder.unWrap(filename());
        parcelImploder.merge(filename());
        auto original = parcelImploder.clean(filename());
        extras::rsi::write_file(original, this->_new_sock);
        std::cout << extras::pass(original) << std::endl;
        std::cout << extras::pass(" uploaded") << std::endl;
    }

    /**
     * @brief Vendor Client/Server ::transfer()
     *
     */
    void rsi::DownloaderServer::transfer() const {
        rsi::Parameter parameter = ~extras::Paths(filename());
        rsi::ParcelImploder parcelImploder;
        auto wrapped = parcelImploder.wrap(filename());
        extras::rsi::send_file2(wrapped, this->_new_sock);
        std::cout << extras::pass(wrapped) << std::endl;
        std::cout << extras::pass(" downloaded") << std::endl;
    }

    void rsi::DownloaderClient::transfer() const {
        rsi::ParcelImploder parcelImploder;
        parcelImploder.unWrap(filename());
        parcelImploder.merge(filename());
        auto original = parcelImploder.clean(filename());
        extras::rsi::write_file(original, this->_sockfd);
        std::cout << extras::pass(original) << std::endl;
        std::cout << extras::pass(" downloaded") << std::endl;
    }




}  // namespace extras
