#include <rsi/sockets/Server.hpp>
#include <rsi/sockets/StatusLine.hpp>
#include <iostream>

using namespace  extras;


int main(int argc, char const* argv[]) {
    try {
        std::cout << rsi::start(argv[0]) << std::endl;
        extras::rsi::ServiceTypeCompilerVendor vendor;
        extras::rsi::SocketPoolServer server(vendor);
        server.parameters(argc, argv);
        server.connect();
        while (true) {
            server.accept();
            server.transfer();
        }
        std::cout << rsi::pass("File sockets allocated successfully") << std::endl;
        server.close();
        std::cout << rsi::end("Closed the connection") << std::endl << std::endl;
        return 0;
    }
    catch (std::exception& ex) {
        std::cout << rsi::fail(ex.what()) << std::endl << std::endl;
        return -1;
    }
}
