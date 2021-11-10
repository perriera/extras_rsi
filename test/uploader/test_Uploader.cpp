#include <rsi/uploader/Uploader.hpp>
#include <extras/strings.hpp>
#include <filesystem>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
namespace fs = std::filesystem;

SCENARIO("Test UploaderInterface: upload", "[UploaderInterface]") {
    std::string target = "send.txt";
    auto uploaded_file = extras::replace_all(target, ".txt", "_uploaded.txt");
    if (fs::exists(uploaded_file)) fs::remove(uploaded_file);
    REQUIRE(fs::exists(target));
    REQUIRE(!fs::exists(uploaded_file));
    system("build/uploader_server send.txt 127.0.0.1 9002 &");
    REQUIRE(system("build/uploader_client send.txt 127.0.0.1 9002") == 0);
    // REQUIRE(!fs::exists(uploaded_file));
    // REQUIRE(fs::exists(target));
}

