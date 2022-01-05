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

#include <extras_rsi/remote/Invocation.hpp>
#include <extras_rsi/socketpool/Server.hpp>
#include <extras/status/StatusLine.hpp>
#include <extras_rsi/subsystem.hpp>
#include <iostream>
#include <extras_rsi/exceptions.hpp>
#include <arpa/inet.h>
#include <unistd.h>

using namespace  extras;


int main(int argc, char const* argv[]) {
    try {
        std::cout << extras::start(argv[0]) << std::endl;

        rsi::PortAuthority portAuthority;
        rsi::ServiceTypeMap clientTasks;
        clientTasks["upload"] = "build/uploader_client";
        clientTasks["vendor"] = "build/vendor_client";
        clientTasks["download"] = "build/downloader_client";
        rsi::ServiceTypeMap serverTasks;
        serverTasks["upload"] = "build/uploader_server";
        serverTasks["vendor"] = "build/vendor_server";
        serverTasks["download"] = "build/downloader_server";

        rsi::Invocation rsi(portAuthority, clientTasks, serverTasks);
        rsi.parse(argc, argv);

        // 
        // setup server socket
        //
        struct sockaddr_in _server_addr;
        int _server_socket = rsi::configure_serversocket(rsi.address().c_str(), stoi(rsi.port()),
            _server_addr, false);
        if (_server_socket == -1) {
            ::close(_server_socket);
            // throw RSIException("Timeout on uploader_server connect", __INFO__);
        }

        // 
        // accept connection
        //
        struct sockaddr_in _new_addr;
        socklen_t addr_size = sizeof(_new_addr);
        int _client_socket = ::accept(_server_socket, (struct sockaddr*)&_new_addr, &addr_size);
        if (_client_socket == -1) {
            ::close(_client_socket);
            // throw RSIException("Timeout on uploader_server accept", __INFO__);
        }

        //
        // handle request
        //
        // auto response = rsi.servicesResponse(_client_socket);



        extras::rsi::ServiceTypeCompilerVendor vendor;
        extras::rsi::SocketPoolServer server(vendor);
        server.parameters(argc, argv);
        server.connect();
        while (true) {
            server.accept();
            server.transfer();
        }
        std::cout << extras::pass("File sockets allocated successfully") << std::endl;
        server.close();
        std::cout << extras::end(argv[0]) << std::endl << std::endl;
        return 0;
    }
    catch (extras::exception& ex) {
        std::cout << ex << std::endl;
        exit(-1);
    }
    catch (std::exception& ex) {
        std::cout << extras::fail(ex.what()) << std::endl;
        exit(-1);
    }
}
