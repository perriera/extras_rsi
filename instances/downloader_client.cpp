#include <rsi/uploader/Downloader.hpp>
#include <rsi/sockets/Status.hpp>
#include <iostream>

using namespace  extras;

int main(int argc, char const* argv[]) {
    try {
        std::cout << rsi::start(argv[0]) << std::endl;
        extras::rsi::DownloaderClient downloader;
        downloader.parameters(argc, argv);
        downloader.connect();
        downloader.transfer();
        std::cout << rsi::pass("File data downloaded successfully") << std::endl;
        downloader.close();
        std::cout << rsi::pass("Closed the connection") << std::endl;
        return 0;
    }
    catch (std::exception& ex) {
        std::cout << rsi::fail(ex.what()) << std::endl;
        return -1;
    }
}
