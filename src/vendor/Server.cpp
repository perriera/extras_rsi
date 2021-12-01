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

#include <rsi/vendor/Vendor.hpp>
#include <rsi/exceptions.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/system.hpp>
#include <ng_imploder/parcel/Parcel.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <rsi/subsystem.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     *  @brief Vendor Client/Server ::transfer()
     *
     *  @note when this method called the time referred to in filename()
     *        is the file specified in the client portion of the code.
     *        this method is now on the server and can avail itself of
     *        whatever the server has to offer, (typically installed
     *        elsewhere and accessible via a system() call).
     *
     *        However, the file will be in 'packed' format. So, to use it
     *        you will have to unpack it, (see below).
     *
     *        This method has at least 20 seconds to get done what it has
     *        to do, (if more time is needed change the timeout value).
     *
     *        Hence it technicaly has all the time in world, (short of a
     *        power outage), to do what it needs to do.
     *
     *        When done, it has repackages the contents.
     *
     */

    void rsi::VendorServer::transfer() const {

        std::string line = read_line_block();
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(line) << std::endl;

        rsi::FileNotFoundException::assertion(filename(), __INFO__);
        std::cout << extras::cyan << extras::pass(" processes file ") << std::endl;
        std::cout << extras::blue << std::endl;
        auto fn = extras::replace_all(filename(), "data/", "data/server/");
        auto cmd = "ls -la " + filename();
        SystemException::assertion(cmd, __INFO__);
        std::cout << std::endl;
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(" lists directory") << std::endl;

        std::string msg = "vendor completed";
        send_line_block(msg);

    }


}  // namespace extras
