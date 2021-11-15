#include <rsi/uploader/Downloader.hpp>
#include <iostream>

int main(int argc, char const* argv[]) {
    try {
        extras::rsi::DownloaderServer downloader;
        downloader.parameters(argc, argv);
        downloader.connect();
        downloader.transfer();
        printf("[+]File data downloaded successfully.\n");
        downloader.close();
        printf("[+]Closed the connection.\n");
        exit(0);
    }
    catch (std::exception& ex) {
        printf("[-]%s.\n", ex.what());
        exit(-1);
    }
}
