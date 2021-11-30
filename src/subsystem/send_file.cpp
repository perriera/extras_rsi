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
 * The above copyright notice and  this permission  notice shall be
 * included in all copies or  substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESSED  OR   IMPLIED,  INCLUDING   BUT  NOT  LIMITED  TO  THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT.  IN  NO  EVENT  SHALL EXPARX  INCORPORATED
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER  IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM, OUT  OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR  OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Except  as  contained  in this  notice, the  name of  the EXPARX
 * INCORPORATED shall not  be used in  advertising or  otherwise to
 * promote the sale, use or other dealings in this Software without
 * prior written authorization from EXPARX INCORPORATED.
 *
 * exparx.com and www.exparx.com  are domain names  registered with
 * EXPARX INCORPORATED, (other GPL-themed licenses are included).
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
