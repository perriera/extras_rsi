#include <rsi/vendor/v1/Vendor.hpp>
#include <rsi/exceptions.hpp>
#include <extras/filesystem/paths.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char const* argv[]) {
    try {
        if (fs::exists("send.txt.txt"))
            fs::remove("send.txt.txt");
        if (fs::exists("send.txt_uploaded"))
            fs::remove("send.txt_uploaded");
        std::string file = "cplusplusorg.freeformjs.imploded.zip";
        auto source = "/home/perry/Projects/extras_rsi/data/" + file;
        auto target = "/tmp/" + file;
        if (fs::exists(target))
            fs::remove(target);
        fs::copy_file(source, target);
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
