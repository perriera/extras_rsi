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

#include <extras/status/StatusLine.hpp>
#include <extras_rsi/remote/Vendor.hpp>
#include <extras_rsi/remote/Invocation.hpp>
#include <extras_rsi/remote/ClientServer.hpp>
#include <extras_rsi/socketpool/Client.hpp>
#include <extras/status/StatusLine.hpp>
#include <extras_rsi/subsystem.hpp>
#include <iostream>
#include <extras_rsi/exceptions.hpp>
#include <arpa/inet.h>
#include <unistd.h>

using namespace  extras;

int main(int argc, char const* argv[]) {
    try {

        //
        // new way
        //

        rsi::PortAuthority portAuthority;
        rsi::Vendor vendor(portAuthority);
        rsi::InvocationClient client(vendor);
        client.parse(argc, argv);
        client.connect();
        client.send();

        //
        // old way
        //

        // std::cout << extras::start(argv[0]) << std::endl;
        // extras::rsi::ServiceTypeCompilerVendor vendor;
        // extras::rsi::SocketPoolClient client(vendor);
        // client.parameters(argc, argv);
        // client.connect();
        // client.transfer();
        // std::cout << extras::pass("File sockets allocated successfully") << std::endl;
        // client.close();
        std::cout << extras::end(argv[0]) << std::endl << std::endl;
        return 0;
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
