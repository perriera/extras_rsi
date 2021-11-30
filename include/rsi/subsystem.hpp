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

#ifndef _EXTRA_RSISUBSYSTEM_HPP
#define _EXTRA_RSISUBSYSTEM_HPP

#include <extras/interfaces.hpp>
#include <iostream>
#include <string>

namespace extras {

    /**
     * @brief rsi: (remote services interface)
     *
     * The following code has been plagerized from other authors
     * and placed here, (where is/as is) as it is code that works
     * and serves a platform for future work when it comes to
     * uploading files over an IP:port connection.
     *
     */
    namespace rsi {

        void send_file(FILE* fp, int sockfd);
        void send_file2(const std::string& filename, int sockfd);

        void write_file(const std::string& filename, int sockfd);

        int connect_to_server(const char* ip, int port,
            struct sockaddr_in& server_addr);
        int configure_serversocket(const char* ip, int port,
            struct sockaddr_in& server_addr,
            bool timeout = true);

        std::string read_string(int sockfd);
        int read_int(int sockfd);
        std::string read_line(int sockfd);

        void send_string(const std::string& msg, int sockfd);
        void send_int(int msg, int sockfd);
        void send_line(const std::string& msg, int sockfd);

        static constexpr int const& SIZE = 1024 * 256;

    }  // namespace rsi

}  // namespace extras

#endif  // _EXTRA_RSISUBSYSTEM_HPP
