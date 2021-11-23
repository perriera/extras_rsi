#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <rsi/sockets/Spinner.hpp>
#include <extras/interfaces.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <rsi/sockets/StatusBar.hpp>
#include <rsi/exceptions.hpp>
#include <rsi/subsystem.hpp>

using namespace std;
using namespace extras;

static void sendIt(int sockfd, const string& buffer) {
    const char* packet = buffer.c_str();
    int size = buffer.size();
    if (send(sockfd, packet, size, 0) == -1) {
        perror("[-]Error in sending file.");
        exit(1);
    }
}

void extras::rsi::send_file2(const std::string& filename, int sockfd) {

    int count = 0;
    int max = StatusBar::linesInFile(filename);
    ifstream in(filename);
    while (in.good()) {
        stringstream ss;
        while (ss.str().size() < 50 * 1024) {
            string line;
            getline(in, line);
            if (line.size() == 0)
                break;
            if (in.good())
                ss << line << endl;
            std::cout << bar(++count, max);
        }
        sendIt(sockfd, ss.str());
    }
    std::cout << "\x1B[2K\r" << extras::rsi::spinner(0) << " ";
    std::cout << extras::cyan << filename << " sent intact" << std::endl;

    sendIt(sockfd, "done");
    for (int i = 0; i < 5000; i++)
        sendIt(sockfd, "JUNK");

}
