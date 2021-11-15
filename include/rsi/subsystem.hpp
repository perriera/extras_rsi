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
