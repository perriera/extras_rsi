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
#include <iostream>
#include <extras/status/StatusLine.hpp>
#include <rsi/subsystem.hpp>

using namespace std;

namespace extras {

    /**
     *  @brief Vendor Client/Server ::transfer()
     *
     */
    void rsi::VendorClient::transfer() const {

        std::string msg = "vendor started";
        send_line(msg);
        std::string status = read_line();
        RemoteDiedException::assertion(status, __INFO__);
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(status) << std::endl;

    }


}  // namespace extras
