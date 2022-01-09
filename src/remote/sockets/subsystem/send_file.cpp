/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <extras_rsi/prototype/gadgets/Spinner.hpp>
#include <extras/interfaces.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras_rsi/prototype/gadgets/StatusBar.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras_rsi/remote/sockets/SubSystem.hpp>

using namespace std;
using namespace extras;

static void sendIt(int sockfd, const string& buffer) {

    /**
     * @brief  FORWARD ERROR CORRECTION
     *
     * extern ssize_t send (int __fd, const void *__buf, size_t __n, int __flags);
     *
     * For reasons unknown, this method of sending files across a socket
     * absolutely insists on putting in a single quote inside the file
     * (twice) as it is sent across. Talk about 'forward error correction'.
     *
     */
    if (extras::str::contains(buffer, "'")) {
        std::cout << "\x1B[2K\r" << " FOUND IT BEFORE IT WENT ACROSS" << std::endl;
        // std::cout << "\x1B[2K\r" << msg << std::endl;
        // buffer = extras::str::replace_all(buffer, "'", "");
    }

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

    in.close();

    auto cpCmd = "cp " + filename + " " + filename + ".sent_copy";
    SystemException::assertion(cpCmd, __INFO__);
    std::cout << std::endl << extras::cyan << filename + ".sent_copy" << " written" << std::endl;

    sendIt(sockfd, "done");
    for (int i = 0; i < 5000; i++)
        sendIt(sockfd, "JUNK");

}
