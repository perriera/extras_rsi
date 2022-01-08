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
#include <extras_rsi/sockets/SubSystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <filesystem>
#include <extras/status/StatusLine.hpp>
#include <extras_arc/wrap.hpp>
#include <extras/filesystem/system.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     * @brief UploaderServer::lock()
     *
     * @param lock
     * @return rsi::Lock
     */
    rsi::Lock rsi::UploaderServer::lock(const rsi::Lock& lock) {
        arc::ParcelImploder parcelImploder(lock);;
        auto wrappedName = parcelImploder.wrapped();
        auto _lock = write_file_block(wrappedName);
        auto ls1 = "ls -la " + wrappedName;
        SystemException::assertion(ls1, __INFO__);
        return _lock;
    }

    /**
     * @brief UploaderServer::unlock()
     *
     * @return rsi::Lock
     */
    rsi::Lock rsi::UploaderServer::unlock(const rsi::Lock&) {
        arc::ParcelImploder parcelImploder(filename());;
        parcelImploder.unWrap();
        parcelImploder.merge();
        auto original = parcelImploder.clean();
        send_line_block("uploader completed");
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass("write_file successful") << std::endl;
        return original;
    }

    /**
     * @brief UploaderServer::transfer()
     *
     */
    void rsi::UploaderServer::transfer() {
        unlock(lock(filename()));
    }

}  // namespace extras
