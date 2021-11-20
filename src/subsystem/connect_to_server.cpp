#include <arpa/inet.h>
#include <unistd.h>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/status/StatusLine.hpp>

int extras::rsi::connect_to_server(const char* ip, int port,
    struct sockaddr_in& server_addr) {
    int e;

    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    SocketException::assertionLTZero(sockfd, "Error in socket", __INFO__);
    std::cout << extras::pass("Server socket created successfully") << std::endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    SocketException::assertionEQMinusOne(e, "Error in socket", __INFO__);
    std::cout << extras::pass("Connected to Server") << std::endl;

    return sockfd;
}