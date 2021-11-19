#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <rsi/sockets/StatusBar.hpp>
#include <rsi/subsystem.hpp>
#include <extras/strings.hpp>

using namespace std;

void extras::rsi::write_file(const std::string& filename, int sockfd) {

    int count = 0;
    int max = StatusBar::lastLinesInFile;
    int n;
    char buffer[extras::rsi::SIZE];

    ofstream out(filename);

    while (true) {
        n = recv(sockfd, buffer, extras::rsi::SIZE, 0);


        std::string msg(buffer);

        auto parts = extras::split(msg, '\n');
        count += parts.size();
        std::cout << bar(count, max);

        if (extras::contains(msg, "done")) {
            msg = extras::replace_all(msg, "done", "");
            msg = extras::replace_all(msg, "J", "");
            msg = extras::replace_all(msg, "U", "");
            msg = extras::replace_all(msg, "N", "");
            msg = extras::replace_all(msg, "K", "");
            out << msg;
            break;
        }

        if (n <= 0) break;
        out << msg;
        bzero(buffer, extras::rsi::SIZE);

    }

    return;
}
