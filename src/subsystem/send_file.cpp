#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include <rsi/exceptions.hpp>
#include <rsi/subsystem.hpp>

void extras::rsi::send_file2(const char* filename, int sockfd) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        throw RSIException("Error in reading file.", __INFO__);
    }
    extras::rsi::send_file(fp, sockfd);
}

void extras::rsi::send_file(FILE* fp, int sockfd) {
    // int n;
    char data[extras::rsi::SIZE] = { 0 };

    while (fgets(data, extras::rsi::SIZE, fp) != NULL) {
        int len = strlen(data);
        if (send(sockfd, data, len, 0) == -1) {
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, extras::rsi::SIZE);
    }
    auto msg = "done";
    std::cout << msg << " sent" << std::endl;
    if (send(sockfd, msg, strlen(msg), 0) == -1) {
        perror("[-]Error in sending file.");
        exit(1);
    }
    //
    auto junk = "JUNK";
    for (int i = 0; i < 10000; i++)
        if (send(sockfd, junk, strlen(junk), 0) == -1) {
            perror("[-]Error in sending file.");
            exit(1);
        }
}
