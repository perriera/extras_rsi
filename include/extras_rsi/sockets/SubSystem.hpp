/**
 * @file subsystem.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief Various (C based) low level I/O socket methods, (for Linux)
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXTRA_RSISUBSYSTEM_HPP
#define _EXTRA_RSISUBSYSTEM_HPP

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

#include <extras/interfaces.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>


namespace extras {

    /**
     * @brief extras_rsi: (remote services interface)
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
            struct sockaddr_in& server_addr,
            bool timeout = true);

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
