#include <rsi/vendor/Vendor.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>

using namespace  extras;

int main(int argc, char const* argv[]) {
    try {
        std::cout << extras::start(argv[0]) << std::endl;
        extras::rsi::VendorClient vendor;
        vendor.parameters(argc, argv);
        vendor.connect();
        vendor.transfer();
        std::cout << extras::pass("File data processed successfully") << std::endl;
        vendor.close();
        std::cout << extras::end("Closed the connection") << std::endl << std::endl;
        return 0;
    }
    catch (std::exception& ex) {
        std::cout << extras::fail(ex.what()) << std::endl << std::endl;
        return -1;
    }
}
