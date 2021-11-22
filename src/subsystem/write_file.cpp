#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <rsi/sockets/StatusBar.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/subsystem.hpp>
#include <extras/strings.hpp>

using namespace std;

void printStatus(const std::string& msg) {

    stringstream ss;
    ss << msg;
    while (ss.good()) {
        string line;
        getline(ss, line);
        if (line.size() > 0) {
            stringstream ss2;
            ss2 << line;
            try {
                extras::rsi::PackedLine packed;
                ss2 >> packed;
                std::cout << "\x1B[2K\r";
                std::cout << extras::rsi::bar(packed.lineNo(), packed.lineCount() + 1);
                std::cout << std::flush;
            }
            catch (extras::rsi::PackedException& ex) {
            }
        }
    }

}

void extras::rsi::write_file(const std::string& filename, int sockfd) {

    int n;
    char buffer[extras::rsi::SIZE];

    ofstream out(filename);

    while (true) {
        n = recv(sockfd, buffer, extras::rsi::SIZE, 0);

        std::string msg(buffer);
        printStatus(msg);

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
