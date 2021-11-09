#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <rsi/sockets/Client.hpp>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char const* argv[]) {
    try {
        extras::rsi::SocketPoolClient client;
        client.parameters(argc, argv);
        client.connect();
        client.transfer();
        // uploader.transfer();
        printf("[+]File data sent successfully.\n");
        // uploader.close();
        printf("[+]Closed the connection.\n");
        client.close();
        return 0;
    }
    catch (std::exception& ex) {
        printf("[-]%s.\n", ex.what());
        return -1;
    }
}
