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
#include <extras_rsi/sockets/StatusBar.hpp>
#include <extras_rsi/sockets/Spinner.hpp>
#include <extras_arc/parcel.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras/strings.hpp>
#include <extras/devices/ansi_colors.hpp>

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
                extras::arc::ParcelLine packed;
                ss2 >> packed;
                std::cout << "\x1B[2K\r";
                std::cout << extras::rsi::bar(packed.lineNo(), packed.lineCount() + 1);
                std::cout << std::flush;
            }
            catch (extras::arc::ParcelException& ex) {
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
    out.close();

    std::cout << "\x1B[2K\r" << extras::rsi::spinner(0) << " ";
    std::cout << extras::cyan << filename << " received intact" << std::endl;

    auto cpCmd = "cp " + filename + " " + filename + ".recevied_copy";
    SystemException::assertion(cpCmd, __INFO__);

    return;
}
