#include <rsi/uploader/Uploader.hpp>
#include <rsi/sockets/Status.hpp>
#include <iostream>

using namespace  extras;

int main(int argc, char const* argv[]) {
    try {
        std::cout << rsi::start(argv[0]) << std::endl;
        extras::rsi::UploaderServer uploader;
        uploader.parameters(argc, argv);
        uploader.connect();
        uploader.transfer();
        std::cout << rsi::pass("File data uploaded successfully") << std::endl;
        uploader.close();
        std::cout << rsi::pass("Closed the connection") << std::endl << std::endl;
        exit(0);
    }
    catch (std::exception& ex) {
        std::cout << rsi::fail(ex.what()) << std::endl << std::endl;
        exit(-1);
    }
}
