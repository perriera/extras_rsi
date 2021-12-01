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
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/status/StatusLine.hpp>

 //
 // https://cdmana.com/2021/02/20210220084428841j.html
 //

int extras::rsi::configure_serversocket(const char* ip, int port,
    struct sockaddr_in& server_addr,
    bool timeoutmode) {
    int sockfd;
    int opt = 1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    SocketException::assertionLTZero(sockfd, "Error in socket", __INFO__);
    std::cout << extras::pass("Server socket created successfully") << std::endl;

    if (timeoutmode) {
        // Set a timeout ...
        struct timeval timeout;
        timeout.tv_sec = 60;  // after 60 seconds connect() will timeout
        timeout.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        std::cout << extras::pass("Server socket times out in 60 seconds") << std::endl;
    }

    // Forcefully attaching socket to the port 
    auto test = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
        sizeof(opt));
    SocketException::assertionNEZero(test, "Error in setsockopt", __INFO__);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    int e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    SocketException::assertionLTZero(e, "Error in bind", __INFO__);
    std::cout << extras::pass("Binding successfull") << std::endl;

    SocketException::assertionNEZero(listen(sockfd, 10), "Error in listening", __INFO__);
    std::cout << extras::pass("Listening") << std::endl;
    return sockfd;
}
