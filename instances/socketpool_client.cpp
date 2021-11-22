#include <rsi/sockets/Client.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>
#include <rsi/exceptions.hpp>

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
        std::cout << extras::end(argv[0]) << std::endl << std::endl;
        return 0;
    }
    catch (rsi::RSIException& ex) {
        std::cout << extras::fail(ex.what()) << std::endl << extras::end(argv[0]) << std::endl;
        std::cout << ex.getfile() << ' ' << ex.getfunc() << ' ' << ex.getline() << std::endl;
        return -1;
    }
    catch (std::exception& ex) {
        std::cout << extras::fail(ex.what()) << std::endl << extras::end(argv[0]) << std::endl;
        return -1;
    }
}
