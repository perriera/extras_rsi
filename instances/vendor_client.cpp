#include <rsi/uploader/Vendor.hpp>
#include <rsi/sockets/StatusLine.hpp>
#include <iostream>

using namespace  extras;

int main(int argc, char const* argv[]) {
    try {
        std::cout << rsi::start(argv[0]) << std::endl;
        extras::rsi::VendorClient vendor;
        vendor.parameters(argc, argv);
        vendor.connect();
        vendor.transfer();
        std::cout << rsi::pass("File data processed successfully") << std::endl;
        vendor.close();
        std::cout << rsi::end("Closed the connection") << std::endl << std::endl;
        return 0;
    }
    catch (std::exception& ex) {
        std::cout << rsi::fail(ex.what()) << std::endl << std::endl;
        return -1;
    }
}
