/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/uploader/Uploader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/parcel/Wrap.hpp>
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
        extras::rsi::send_file2(filename, this->_sockfd);
    }

    void rsi::UploaderClient::send_line(const rsi::UploaderStatus& msg) const {
        extras::rsi::send_line(msg, this->_sockfd);
    }

    rsi::UploaderStatus rsi::UploaderClient::read_line() const {
        return extras::rsi::read_line(this->_sockfd);
    }

    rsi::Filename rsi::UploaderClient::write(const Filename& filename) const {
        extras::rsi::write_file(filename, this->_sockfd);
        return filename;
    }

    /**
     * @brief UploaderClient::lock()
     *
     * @param lock
     * @return rsi::Lock
     */
    rsi::Lock rsi::UploaderClient::lock(const rsi::Lock& lock) const {
        rsi::FileNotFoundException::assertion(lock, __INFO__);
        rsi::ParcelImploder parcelImploder;
        auto wrapped = parcelImploder.wrap(lock);
        rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        send(wrapped);
        return lock;
    }

    /**
     * @brief UploaderClient::unlock()
     *
     * @param lock
     * @return rsi::Lock
     */
    rsi::Lock rsi::UploaderClient::unlock(const rsi::Lock& lock) const {
        auto status = read_line();
        rsi::ParcelImploder parcelImploder;
        parcelImploder.clean(lock);
        RemoteDiedException::assertion(status, __INFO__);
        std::cout << extras::pass(lock) << std::endl;
        std::cout << extras::pass(status) << std::endl;
        std::cout << extras::pass("send_file2 successful") << std::endl;
        return lock;
    }

    /**
     * @brief UploaderClient::transfer()
     *
     */
    void rsi::UploaderClient::transfer() const {
        unlock(lock(filename()));
    }

}  // namespace extras
