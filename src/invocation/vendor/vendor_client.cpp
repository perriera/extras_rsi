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
#include <extras/status/StatusLine.hpp>
#include <extras_rsi/remote/sockets/SubSystem.hpp>
#include <iostream>
#include <extras_rsi/exceptions.hpp>

using namespace  extras;

int extras::rsi::vendor_client(int argc, char const* argv[]) {
    try {
        std::cout << extras::start(argv[0]) << std::endl;
        extras::rsi::VendorClient vendor;
        vendor.parameters(argc, argv);
        vendor.connect();
        vendor.transfer();
        std::cout << extras::pass("File data processed successfully") << std::endl;
        vendor.close();
        std::cout << extras::end(argv[0]) << std::endl << std::endl;
        return 0;
    }
    catch (extras::HelpParameterException& ex) {
        ex.getHelp("HOWTO-vendor.md");
        return -1;
    }
    catch (extras::exception& ex) {
        std::cout << ex << std::endl;
        return -1;
    }
    catch (std::exception& ex) {
        std::cout << extras::fail(ex.what()) << std::endl;
        return -1;
    }
}
