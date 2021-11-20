#include <rsi/uploader/Uploader.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>

using namespace  extras;

int main(int argc, char const* argv[]) {
    try {
        std::cout << extras::start(argv[0]) << std::endl;
        extras::rsi::UploaderClient uploader;
        uploader.parameters(argc, argv);
        uploader.connect();
        uploader.transfer();
        std::cout << extras::pass("File data uploaded successfully") << std::endl;
        uploader.close();
        std::cout << extras::end("Closed the connection") << std::endl << std::endl;
        return 0;
    }
    catch (std::exception& ex) {
        std::cout << extras::fail(ex.what()) << std::endl << std::endl;
        return -1;
    }
}
