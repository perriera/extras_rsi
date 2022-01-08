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

#include <extras_rsi/service/Uploader.hpp>
#include <extras_rsi/remote/sockets/SubSystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>
#include <extras_arc/parcel.hpp>
#include <extras_arc/wrap.hpp>
#include <filesystem>
#include <extras/filesystem/system.hpp>

namespace fs = std::filesystem;

using namespace std;

namespace extras {

    /**
     * @brief UploaderClient::lock()
     *
     * @param lock
     * @return rsi::Lock
     */
    rsi::Lock rsi::UploaderClient::lock(const rsi::Lock& lock) {
        rsi::FileNotFoundException::assertion(lock, __INFO__);
        arc::ParcelImploder parcelImploder(lock);
        auto wrapped = parcelImploder.wrap();
        rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        send_file_block(wrapped);
        return lock;
    }

    /**
     * @brief UploaderClient::unlock()
     *
     * @param lock
     * @return rsi::Lock
     */
    rsi::Lock rsi::UploaderClient::unlock(const rsi::Lock& lock) {
        auto status = read_line_block();
        arc::ParcelImploder parcelImploder(lock);;
        parcelImploder.clean();
        RemoteBlockException::assertion(status, __INFO__);
        std::cout << extras::pass(lock) << std::endl;
        std::cout << extras::pass(status) << std::endl;
        std::cout << extras::pass("send_file2 successful") << std::endl;
        return lock;
    }

    /**
     * @brief UploaderClient::transfer()
     *
     */
    void rsi::UploaderClient::transfer() {
        unlock(lock(filename()));
    }

}  // namespace extras
