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
#include <extras/filesystem/system.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     * @brief Uploader Client/Server ::transfer()
     *
     */
    void rsi::UploaderClient::transfer() const {
        // auto fn = filename();
        // rsi::FileNotFoundException::assertion(filename(), __INFO__);
        // send(filename());
        // std::cout << extras::pass("send_file2 successful") << std::endl;

        auto fn = filename();
        rsi::FileNotFoundException::assertion(fn, __INFO__);
        // send(filename());
        rsi::ParcelImploder parcelImploder;
        auto wrapped = parcelImploder.wrap(fn);
        rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        // // wrapped_parcel = wrapped;
        send(wrapped);
        // std::cout << extras::pass(wrapped) << std::endl;
        std::cout << extras::pass("send_file2 successful") << std::endl;

        // rsi::FileNotFoundException::assertion(filename(), __INFO__);
        // rsi::ParcelImploder parcelImploder;
        // auto wrapped = parcelImploder.wrap(filename());
        // rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        // // wrapped_parcel = wrapped;
        // extras::rsi::send_file2(wrapped, this->_sockfd);
        // std::cout << extras::pass(wrapped) << std::endl;
        // std::cout << extras::pass("send_file2 successful") << std::endl;
    }

    void rsi::UploaderServer::transfer() const {
        // auto fn = filename();
        // fn = write(filename());
        // rsi::FileNotFoundException::assertion(fn, __INFO__);
        // std::cout << extras::pass(fn) << std::endl;
        // std::cout << extras::pass("write_file successful") << std::endl;

        static std::string server_dir = "data/server/";

        auto fn = filename();
        // fn = write(filename());
        // rsi::FileNotFoundException::assertion(fn, __INFO__);
        rsi::ParcelImploder parcelImploder;
        auto wrappedName = parcelImploder.wrapped(fn);
        wrappedName = write(wrappedName);
        fn = extras::replace_all(fn, "data/", server_dir);
        rsi::FileNotFoundException::assertion(wrappedName, __INFO__);
        parcelImploder.unWrap(fn);
        parcelImploder.merge(fn);
        auto original = parcelImploder.clean(fn);
        std::cout << extras::pass(fn) << std::endl;
        std::cout << extras::pass("write_file successful") << std::endl;

        // rsi::ParcelImploder parcelImploder;
        // auto wrappedName = parcelImploder.wrapped(filename());
        // extras::rsi::write_file(wrappedName, this->_new_sock);
        // rsi::FileNotFoundException::assertion(wrappedName, __INFO__);
        // parcelImploder.unWrap(filename());
        // parcelImploder.merge(filename());
        // auto original = parcelImploder.clean(filename());
        // auto test = fs::exists(filename());
        // auto msg = (test ? "write_file successful" : "did not upload");
        // std::cout << extras::pass(filename()) << std::endl;
        // std::cout << extras::pass(msg) << std::endl;
    }

    /**
     * @brief Vendor Client/Server ::transfer()
     *
     */
    void rsi::DownloaderServer::transfer() const {
        rsi::FileNotFoundException::assertion(filename(), __INFO__);
        rsi::ParcelImploder parcelImploder;
        auto wrapped = parcelImploder.wrap(filename());
        rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        // wrapped_parcel = wrapped;
        extras::rsi::send_file2(wrapped, this->_new_sock);
        std::cout << extras::pass(wrapped) << std::endl;
        std::cout << extras::pass("send_file2 successful") << std::endl;
    }

    void rsi::DownloaderClient::transfer() const {
        rsi::ParcelImploder parcelImploder;
        auto check = parcelImploder.wrapped(filename());
        extras::rsi::write_file(check, this->_sockfd);
        rsi::FileNotFoundException::assertion(check, __INFO__);
        parcelImploder.unWrap(filename());
        parcelImploder.merge(filename());
        auto original = parcelImploder.clean(filename());
        rsi::FileNotFoundException::assertion(original, __INFO__);
        std::cout << extras::pass(original) << std::endl;
        std::cout << extras::pass("write_file successful") << std::endl;
        //
        std::cout << extras::cyan << extras::pass(" updated file ");
        std::cout << extras::blue << std::endl;
        auto cmd = "ls -la " + original;
        SystemException::assertion(cmd, __INFO__);
    }




}  // namespace extras
