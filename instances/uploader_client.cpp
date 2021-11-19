#include <rsi/uploader/Uploader.hpp>
#include <rsi/sockets/StatusLine.hpp>
#include <iostream>

using namespace  extras;

int main(int argc, char const* argv[]) {
    try {
        std::cout << rsi::start(argv[0]) << std::endl;
        extras::rsi::UploaderClient uploader;
        uploader.parameters(argc, argv);
        uploader.connect();
        uploader.transfer();
        std::cout << rsi::pass("File data uploaded successfully") << std::endl;
        uploader.close();
        std::cout << rsi::end(argv[0]) << std::endl << std::endl;
        return 0;
    }
    catch (std::exception& ex) {
        std::cout << rsi::fail(ex.what()) << std::endl << std::endl;
        return -1;
    }
}
