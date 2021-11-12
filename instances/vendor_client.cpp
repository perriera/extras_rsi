#include <rsi/uploader/Vendor.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char const* argv[]) {
    try {
        if (fs::exists("send.txt.txt"))
            fs::remove("send.txt.txt");
        if (fs::exists("send.txt_uploaded"))
            fs::remove("send.txt_uploaded");
        extras::rsi::VendorClient vendor;
        vendor.parameters(argc, argv);
        vendor.connect();
        vendor.transfer();
        printf("[+]File data uploaded successfully.\n");
        vendor.close();
        printf("[+]Closed the connection.\n");
        return 0;
    }
    catch (std::exception& ex) {
        printf("[-]%s.\n", ex.what());
        return -1;
    }
}
