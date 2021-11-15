#include <rsi/uploader/Uploader.hpp>
#include <iostream>

int main(int argc, char const* argv[]) {
    try {
        extras::rsi::UploaderClient uploader;
        uploader.parameters(argc, argv);
        uploader.connect();
        uploader.transfer();
        printf("[+]File data uploaded successfully.\n");
        uploader.close();
        printf("[+]Closed the connection.\n");
        return 0;
    }
    catch (std::exception& ex) {
        printf("[-]%s.\n", ex.what());
        return -1;
    }
}
