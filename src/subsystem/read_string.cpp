#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <rsi/subsystem.hpp>
#include <extras/strings.hpp>
#include <string>

std::string exparx::rsi::read_string(int sockfd) {
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

int exparx::rsi::read_int(int sockfd) {
    std::string msg = read_string(sockfd);
    return std::stoi(msg);
}

std::string exparx::rsi::read_line(int sockfd) {
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