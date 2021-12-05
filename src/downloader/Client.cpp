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

#include <extras_rsi/uploader/Uploader.hpp>
#include <extras_rsi/uploader/Downloader.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras_arc/parcel.hpp>
#include <iostream>
#include <filesystem>
#include <extras/status/StatusLine.hpp>
#include <extras_arc/wrap.hpp>
#include <extras/filesystem/system.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     * @brief DownloaderClient::lock()
     *
     * @param lock
     * @return rsi::Lock
     */
    rsi::Lock rsi::DownloaderClient::lock(const rsi::Lock& lock) {
        arc::ParcelImploder parcelImploder(lock);
        auto wrappedName = parcelImploder.wrapped();
        write_file_block(wrappedName);
        return lock;
    }

    /**
     * @brief DownloaderClient::unlock()
     *
     * @param lock
     * @return rsi::Lock
     */
    rsi::Lock rsi::DownloaderClient::unlock(const rsi::Lock& lock) {
        arc::ParcelImploder parcelImploder(lock);;
        parcelImploder.unWrap();
        parcelImploder.merge();
        parcelImploder.clean();
        std::cout << extras::pass(lock) << std::endl;
        std::cout << extras::pass("write_file successful") << std::endl;
        std::string msg = "downloader completed";
        send_line_block(msg);
        return lock;
    }

    /**
     * @brief DownloaderClient::transfer()
     *
     */
    void rsi::DownloaderClient::transfer() {
        unlock(lock(filename()));
    }

}  // namespace extras
