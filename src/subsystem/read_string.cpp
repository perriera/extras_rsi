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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <extras_rsi/subsystem.hpp>
#include <extras/strings.hpp>
#include <string>

std::string extras::rsi::read_string(int sockfd) {
    std::string result;
    char buffer[1024];
    int n;

    while (1) {
        n = recv(sockfd, buffer, 1024, 0);
        if (n <= 0) break;
        result += buffer;
        bzero(buffer, 1024);
    }
    return result;
}

int extras::rsi::read_int(int sockfd) {
    std::string msg = read_string(sockfd);
    return std::stoi(msg);
}

std::string extras::rsi::read_line(int sockfd) {
    std::string result;
    char buffer[1024];
    bzero(buffer, 1024);
    int n;

    while (1) {
        n = recv(sockfd, buffer, 1024, 0);
        if (n <= 0) break;
        result += buffer;
        if (extras::contains(result, "\n")) break;
        bzero(buffer, 1024);
    }
    result = extras::replace_all(result, "\n", "");

    return result;
}