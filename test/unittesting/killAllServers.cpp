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

#include <extras_rsi/service/uploader/Uploader.hpp>
#include <extras_rsi/prototype/socketpool/SocketPool.hpp>
#include <extras/strings.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <extras_rsi/prototype/socketpool/Client.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>
#include <extras_rsi/exceptions.hpp>
#include <chrono>
#include <thread>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;
namespace fs = std::filesystem;

void killServers(std::string pattern) {
    try {
        rsi::SocketPool::killServers(pattern);
    }
    catch (const extras::rsi::NoServersToKillException& ex) {
    }
}

void killAllServers() {
    killServers("rsi_server");
    killServers("socketpool_serv");
    killServers("uploader_server");
    killServers("downloader_serv");
    killServers("vendor_server");
    REQUIRE_THROWS_AS(rsi::SocketPool::killServers("rsi_server"), extras::rsi::NoServersToKillException);
    REQUIRE_THROWS_AS(rsi::SocketPool::killServers("socketpool_serv"), extras::rsi::NoServersToKillException);
    REQUIRE_THROWS_AS(rsi::SocketPool::killServers("uploader_server"), extras::rsi::NoServersToKillException);
    REQUIRE_THROWS_AS(rsi::SocketPool::killServers("downloader_serv"), extras::rsi::NoServersToKillException);
    REQUIRE_THROWS_AS(rsi::SocketPool::killServers("vendor_server"), extras::rsi::NoServersToKillException);
}
