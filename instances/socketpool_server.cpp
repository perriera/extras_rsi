#include <rsi/sockets/Server.hpp>
#include <iostream>


int main(int argc, char const* argv[]) {
    try {
        extras::rsi::ServiceTypeCompilerVendor vendor;
        extras::rsi::SocketPoolServer server(vendor);
        server.parameters(argc, argv);
        server.connect();
        while (true) {
            server.accept();
            server.transfer();
        }
        printf("[+]File data sent successfully.\n");
        server.close();
        printf("[+]Closed the connection.\n\n");
        return 0;
    }
    catch (std::exception& ex) {
        printf("[-]%s.\n", ex.what());
        return -1;
    }
}
