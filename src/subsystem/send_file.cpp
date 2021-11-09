#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <rsi/exceptions.hpp>
#include <rsi/subsystem.hpp>

void exparx::rsi::send_file2(const char* filename, int sockfd) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        throw RSIException("Error in reading file.", __INFO__);
    }
    exparx::rsi::send_file(fp, sockfd);
}

void exparx::rsi::send_file(FILE* fp, int sockfd) {
    // int n;
    char data[exparx::rsi::SIZE] = { 0 };

    while (fgets(data, exparx::rsi::SIZE, fp) != NULL) {
        int len = strlen(data);
        if (send(sockfd, data, len, 0) == -1) {
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, exparx::rsi::SIZE);
    }
}
