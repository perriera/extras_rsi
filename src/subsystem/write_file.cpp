#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include <rsi/subsystem.hpp>
#include <extras/strings.hpp>
using namespace std;

void extras::rsi::write_file(const char* filename, int sockfd) {
    int n;
    char buffer[extras::rsi::SIZE];

    ofstream out(filename);

    while (true) {
        n = recv(sockfd, buffer, extras::rsi::SIZE, 0);

        std::string msg(buffer);
        std::cout << msg;
        if (extras::contains(msg, "done")) {
            std::cout << msg << std::endl;
            msg = extras::replace_all(msg, "done", "");
            msg = extras::replace_all(msg, "J", "");
            msg = extras::replace_all(msg, "U", "");
            msg = extras::replace_all(msg, "N", "");
            msg = extras::replace_all(msg, "K", "");
            std::cout << msg << std::endl;
            out << msg;
            break;
        }

        if (n <= 0) break;
        out << msg;
        bzero(buffer, extras::rsi::SIZE);

    }

    // while (true) {
    //     bzero(buffer, extras::rsi::SIZE);
    //     n = recv(sockfd, buffer, extras::rsi::SIZE, 0);
    //     if (n <= 0) break;
    // }

    return;
}

// build/uploader_client data/cplusplusorg.freeformjs.imploded.zip 137.184.218.130 9003
// build/uploader_server send.txt 137.184.218.130 9003

// build/uploader_client data/cplusplusorg.freeformjs.imploded.zip 137.184.218.130 9003
// build/uploader_server send.txt 137.184.218.130 9003

