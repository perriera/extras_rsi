/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

#include <rsi/uploader/Uploader.hpp>
#include <extras/strings.hpp>
#include <filesystem>
#include <iostream>


 // build/uploader_client data/cplusplusorg.freeformjs.imploded.zip 137.184.218.130 9003
 // build/uploader_server send.txt 137.184.218.130 9003

 // build/uploader_client data/cplusplusorg.freeformjs.imploded.zip 137.184.218.130 9003
 // build/uploader_server send.txt 137.184.218.130 9003

 // build/_deps/rsi-build/socketpool_server 127.0.0.1 8080 send.txt  
 // build/_deps/rsi-build/socketpool_client 127.0.0.1 8080 data/cplusplusorg.freeformjs.imploded.zip upload vendor download

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

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

