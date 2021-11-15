#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <extras/interfaces.hpp>
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
        }
        sendIt(sockfd, ss.str());
    }
    sendIt(sockfd, "done");
    for (int i = 0; i < 5000; i++)
        sendIt(sockfd, "JUNK");

}
