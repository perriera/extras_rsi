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

#include <extras_rsi/services/SessionType.hpp>
#include <extras_rsi/socketpool/Parameters.hpp>
#include <extras/filesystem/filesystem.hpp>
#include <extras_rsi/socketpool/Client.hpp>
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
    extras::Directory directory = "/tmp/token";

    rsi::Session session;
    rsi::SessionInterface& i = session;

    REQUIRE(!i.exists());
    i.open();
    REQUIRE(fs::exists(i.session()));
    directory = i.session();
    REQUIRE(i.exists());
    auto fn1 = extras::FileSystem(pathname).filename();
    auto fn2 = extras::FileSystem(directory).append(fn1);
    auto correct_answer = fn2;
    REQUIRE(i.entry_name(pathname) == correct_answer);
    REQUIRE(!i.active());
    i.add(pathname);
    REQUIRE(i.active());
    i.remove(pathname);
    REQUIRE(!i.active());
    i.close();
    REQUIRE(!i.exists());
    REQUIRE(!i.active());

    rsi::RequestType after = "vendor 137.184.218.130 9002 ";
    auto fn3 = extras::FileSystem(directory).append("/src.zip");
    auto fn4 = extras::FileSystem(directory).append("/exparx.webflow.zip");
    after += fn3 + " " + fn4 + " ";
    REQUIRE(i.sessionType(before) == after);

}
