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
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/status/StatusLine.hpp>

int extras::rsi::connect_to_server(const char* ip, int port,
    struct sockaddr_in& server_addr) {
    int e;

    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    SocketException::assertionLTZero(sockfd, "Error in socket", __INFO__);
    std::cout << extras::pass("Server socket created successfully") << std::endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    SocketException::assertionEQMinusOne(e, "Error in socket", __INFO__);
    std::cout << extras::pass("Connected to Server") << std::endl;

    return sockfd;
}