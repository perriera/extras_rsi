#include <rsi/uploader/Uploader.hpp>
#include <extras/strings.hpp>
#include <filesystem>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
namespace fs = std::filesystem;

SCENARIO("Test UploaderInterface: download", "[UploaderInterface]") {
    std::string target = "send.txt";
    auto downloaded_file = extras::replace_all(target, ".txt", "_downloaded.txt");
    if (fs::exists(downloaded_file)) fs::remove(downloaded_file);
    REQUIRE(fs::exists(target));
    REQUIRE(!fs::exists(downloaded_file));
    system("build/downloader_server send.txt 127.0.0.1 9003 &");
    REQUIRE(system("build/downloader_client send.txt 127.0.0.1 9003") == 0);
    REQUIRE(fs::exists(downloaded_file));
    // REQUIRE(fs::exists(target));
}
