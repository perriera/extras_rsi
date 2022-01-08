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
#include <extras_rsi/sockets/SubSystem.hpp>
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
     * @brief DownloaderServer::lock()
     *
     * @param lock
     * @return rsi::Lock
     */

    rsi::Lock rsi::DownloaderServer::lock(const rsi::Lock& lock) {
        rsi::FileNotFoundException::assertion(lock, __INFO__);
        arc::ParcelImploder parcelImploder(lock);
        auto wrapped = parcelImploder.wrap();
        rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        send_file_block(wrapped);
        std::cout << extras::pass("send_file2 successful") << std::endl;
        return lock;
    }

    /**
     * @brief DownloaderServer::unlock()
     *
     * @param lock
     * @return rsi::Lock
     */

    rsi::Lock rsi::DownloaderServer::unlock(const rsi::Lock& lock) {
        std::string status = read_line_block();
        arc::ParcelImploder parcelImploder(lock);
        parcelImploder.clean();
        auto rm_cmd = "rm " + lock;
        SystemException::assertion(rm_cmd, __INFO__);
        RemoteBlockException::assertion(status, __INFO__);
        std::cout << extras::pass(lock) << std::endl;
        std::cout << extras::pass(status) << std::endl;
        return lock;
    }

    /**
     * @brief DownloaderServer::transfer()
     *
     */
    void rsi::DownloaderServer::transfer() {
        unlock(lock(filename()));
    }

}  // namespace extras
