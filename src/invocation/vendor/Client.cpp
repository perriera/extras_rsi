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

#include <extras_rsi/invocation/vendor/Client.hpp>
#include <extras_rsi/invocation/vendor/Server.hpp>
#include <iostream>
#include <extras/devices/ansi_colors.hpp>
#include <extras/status/StatusLine.hpp>
#include <extras_rsi/remote/sockets/SubSystem.hpp>

using namespace std;

namespace extras {

    /**
     *  @brief Vendor Client/Server ::transfer()
     *
     */
    void rsi::VendorClient::transfer() {

        std::string msg = "vendor started";
        send_line_block(msg);

        std::cout << extras::cyan << extras::pass(" processes file: ") << filename() << std::endl;
        rsi::FileNotFoundException::assertion(filename(), __INFO__);
        auto ls1 = "ls -la " + filename();
        SystemException::assertion(ls1, __INFO__);
        for (auto extra : this->extra_files()) {
            rsi::FileNotFoundException::assertion(extra, __INFO__);
            std::cout << extras::cyan << extras::pass(" processes file: ") << extra << std::endl;
            auto ls1 = "ls -la " + extra;
            SystemException::assertion(ls1, __INFO__);
        }

        std::string status = read_line_block();
        RemoteBlockException::assertion(status, __INFO__);
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(status) << std::endl;

    }


}  // namespace extras
