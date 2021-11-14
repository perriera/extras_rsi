#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <rsi/subsystem.hpp>
#include <extras/strings.hpp>

void extras::rsi::write_file(const char* filename, int sockfd) {
    int n;
    FILE* fp;
    char buffer[extras::rsi::SIZE];

    fp = fopen(filename, "w");

    bool DONE = false;

    while (!DONE) {
        n = recv(sockfd, buffer, extras::rsi::SIZE, 0);

        std::string msg(buffer);
        if (extras::contains(msg, "done")) {
            msg = extras::replace_all(msg, "done", "");
            bzero(buffer, extras::rsi::SIZE);
            for (int i = 0; i < msg.size(); i++)
                buffer[i] = msg[i];
            DONE = true;
        }

        if (n <= 0) break;
        fprintf(fp, "%s", buffer);
        bzero(buffer, extras::rsi::SIZE);
    }
    return;
}

