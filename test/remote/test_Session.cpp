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

#include <extras_rsi/remote/SessionType.hpp>
#include <extras_rsi/prototype/socketpool/Parameters.hpp>
#include <extras/filesystem/filesystem.hpp>
#include <extras_rsi/prototype/socketpool/Client.hpp>
#include <iostream>
#include <filesystem>
#include <string.h>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Test SessionInterface: clients", "[SessionInterface]") {

    extras::Pathname pathname = "data/exparx.webflow.zip";
    rsi::RequestType before = "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip";
    extras::Directory _directory = "/tmp/token";

    rsi::Session session;
    rsi::SessionInterface& i = session;

    REQUIRE(!i.exists());
    i.create();
    REQUIRE(fs::exists(i.session()));
    _directory = i.session();
    REQUIRE(i.exists());
    auto fn1 = extras::FileSystem(pathname).filename();
    auto fn2 = extras::FileSystem(_directory).append(fn1);
    auto correct_answer = fn2;
    REQUIRE(i.entry_name(pathname) == correct_answer);
    REQUIRE(!i.active());
    i.add(pathname);
    REQUIRE(i.active());

    rsi::RequestTypeList request_list = {
        "build/uploader_server 137.184.218.130 9000 data/src.zip",
        "build/uploader_server 137.184.218.130 9001 data/exparx.webflow.zip",
        "build/vendor_server 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip",
        "build/downloader_server 137.184.218.130 9003 data/src.zip"
    };

    rsi::ServiceTypeList servers_list = {
        "build/uploader_server 137.184.218.130 9000 /tmp/$token/data/src.zip",
        "build/uploader_server 137.184.218.130 9001 /tmp/$token/data/exparx.webflow.zip",
        "build/vendor_server 137.184.218.130 9002 /tmp/$token/data/src.zip /tmp/$token/data/exparx.webflow.zip",
        "build/downloader_server 137.184.218.130 9003 /tmp/$token/data/src.zip",
    };

    rsi::ServiceTypeList updated_servers_list;
    for (auto item : servers_list) {
        auto updated = extras::str::replace_all(item, "/tmp/$token/data", _directory) + " ";
        updated_servers_list.push_back(updated);
    }

    auto afterList = i.sessionTypeList(request_list);
    REQUIRE(afterList == updated_servers_list);

    i.remove(pathname);
    REQUIRE(!i.active());
    i.destroy();
    REQUIRE(!i.exists());
    REQUIRE(!i.active());

    rsi::RequestType after = "vendor 137.184.218.130 9002 ";
    auto fn3 = extras::FileSystem(_directory).append("/src.zip");
    auto fn4 = extras::FileSystem(_directory).append("/exparx.webflow.zip");
    after += fn3 + " " + fn4 + " ";
    auto test = i.sessionType(before);
    REQUIRE(test == after);

    SystemException::assertion("rm -rf testit;rm -rf testit2;rm -rf runtime;", __INFO__);

}
