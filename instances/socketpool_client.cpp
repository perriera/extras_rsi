#include <rsi/sockets/Client.hpp>
#include <iostream>

int main(int argc, char const* argv[]) {
    try {
        extras::rsi::SocketPoolClient client;
        client.parameters(argc, argv);
        client.connect();
        client.transfer();
        printf("[+]File data sent successfully.\n");
        client.close();
        printf("[+]Closed the connection.\n");
        return 0;
    }
    catch (std::exception& ex) {
        printf("[-]%s.\n", ex.what());
        return -1;
    }
}
