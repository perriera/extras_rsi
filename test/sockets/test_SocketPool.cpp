#include <rsi/uploader/Uploader.hpp>
#include <extras/strings.hpp>
#include <filesystem>
#include <iostream>

#include "../vendor/catch.hpp"
#include "../vendor/fakeit.hpp"

using namespace extras;
namespace fs = std::filesystem;

// SCENARIO("Test SocketPoolInterface: upload", "[SocketPoolInterface]") {
//     std::string target = "send.txt";
//     auto uploaded_file = extras::replace_all(target, ".txt", "_uploaded.txt");
//     if (fs::exists(uploaded_file)) fs::remove(uploaded_file);
//     REQUIRE(fs::exists(target));
//     REQUIRE(!fs::exists(uploaded_file));
//     system("build/socketpool_server 127.0.0.1 8080 send.txt upload download &");
//     REQUIRE(system("build/socketpool_client 127.0.0.1 8080 send.txt upload download ") == 0);
//     REQUIRE(!fs::exists(uploaded_file));
//     REQUIRE(fs::exists(target));
// }

