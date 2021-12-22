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

#include <extras_rsi/uploader/Uploader.hpp>
#include <extras/strings.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>


 // build/uploader_client data/cplusplusorg.freeformjs.imploded.zip 137.184.218.130 9003
 // build/uploader_server send.txt 137.184.218.130 9003

 // build/uploader_client data/cplusplusorg.freeformjs.imploded.zip 137.184.218.130 9003
 // build/uploader_server send.txt 137.184.218.130 9003

 // build/_deps/extras_rsi-build/socketpool_server 127.0.0.1 8080 send.txt  
 // build/_deps/extras_rsi-build/socketpool_client 127.0.0.1 8080 data/cplusplusorg.freeformjs.imploded.zip upload vendor download

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
namespace fs = std::filesystem;

void killServers(std::string pattern) {
    auto file = "list.txt";
    auto report = "ps -A | grep \"" + pattern + "\" > " + file;
    try {
        SystemException::assertion(report, __INFO__);
        std::ifstream in(file);
        while (in.good()) {
            std::string word;
            std::string line;
            in >> word;
            getline(in, line);
            if (word != "" && extras::contains(line, pattern)) {
                auto kill = "kill " + word;
                SystemException::assertion(kill, __INFO__);
            }
        }
    }
    catch (SystemException& ex) {
        std::cout << ex << std::endl;
    }
}

SCENARIO("Test SocketPoolInterface: upload", "[SocketPoolInterface]") {
    extras::Parameters args = { "127.0.0.1", "8080", "9000-9500" };
    killServers("socketpool_serv");
    system("build/socketpool_server 127.0.0.1 8080 9000-9500 &");
    killServers("socketpool_serv");
    //    REQUIRE(system("build/socketpool_client 127.0.0.1 8080 send.txt upload download ") == 0);
}

