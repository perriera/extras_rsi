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

#include <rsi/subsystem.hpp>
#include <string>

void extras::rsi::send_string(const std::string& msg, int sockfd) {
    if (send(sockfd, msg.c_str(), msg.length(), 0) == -1) {
        perror("[-]Error in sending string.");
        exit(1);
    }
}

void extras::rsi::send_int(int msg, int sockfd) {
    std::string value = std::to_string(msg);
    return send_string(value, sockfd);
}

void extras::rsi::send_line(const std::string& msg, int sockfd) {
    std::string line = msg + "\n";
    if (send(sockfd, line.c_str(), line.length(), 0) == -1) {
        perror("[-]Error in sending string.");
        exit(1);
    }
}
