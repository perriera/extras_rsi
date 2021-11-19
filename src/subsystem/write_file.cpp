#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <rsi/sockets/StatusBar.hpp>
#include <rsi/parcel/Line.hpp>
#include <rsi/subsystem.hpp>
#include <extras/strings.hpp>

using namespace std;

void extras::rsi::write_file(const std::string& filename, int sockfd) {

    int count = 0;
    int n;
    char buffer[extras::rsi::SIZE];

    ofstream out(filename);

    while (true) {
        n = recv(sockfd, buffer, extras::rsi::SIZE, 0);

        //
        //
        std::string msg(buffer);
        auto parts = extras::split(msg, '\n');
        count += parts.size();
        stringstream ss;
        ss << msg;
        string line, line2;
        getline(ss, line);
        getline(ss, line);
        getline(ss, line2);
        if (line2.size() > 0) {
            stringstream ss2;
            ss2 << line;
            PackedLine packed;
            ss2 >> packed;
            std::cout << bar(count, packed.maxCount());
        }
        //
        //

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
    std::cout << std::endl;

    return;
}
