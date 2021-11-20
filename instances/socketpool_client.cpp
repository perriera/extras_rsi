#include <rsi/sockets/Client.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>

using namespace  extras;

int main(int argc, char const* argv[]) {
    try {
        std::cout << extras::start(argv[0]) << std::endl;
        extras::rsi::ServiceTypeCompilerVendor vendor;
        extras::rsi::SocketPoolClient client(vendor);
        client.parameters(argc, argv);
        client.connect();
        client.transfer();
        std::cout << extras::pass("File sockets allocated successfully") << std::endl;
        client.close();
        std::cout << extras::end("Closed the connection") << std::endl << std::endl;
        return 0;
    }
    catch (std::exception& ex) {
        std::cout << extras::fail(ex.what()) << std::endl << std::endl;
        return -1;
    }
}
