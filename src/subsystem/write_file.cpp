#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <rsi/subsystem.hpp>

void exparx::rsi::write_file(const char* filename, int sockfd) {
    int n;
    FILE* fp;
    char buffer[exparx::rsi::SIZE];

    fp = fopen(filename, "w");
    while (1) {
        n = recv(sockfd, buffer, exparx::rsi::SIZE, 0);
        if (n <= 0) break;
        fprintf(fp, "%s", buffer);
        bzero(buffer, exparx::rsi::SIZE);
    }
    return;
}