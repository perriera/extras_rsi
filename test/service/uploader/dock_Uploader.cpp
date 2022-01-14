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
#include <extras/strings.hpp>
#include <extras_arc/wrap.hpp>
#include <extras_arc/parcel.hpp>
#include <extras_arc/wrap.hpp>
#include <extras_rsi/remote/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras_arc/imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>

#include "../../unittesting/catch.hpp"
#include "../../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Dock UploaderInterface: basic2", "[UploaderInterface]") {

    rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    rsi::Parameter _program = "uploader_client";
    rsi::Parameter _filename = original;
    rsi::Parameter _ip = "127.0.0.1";
    rsi::Parameter _port = "8080";

    Mock<rsi::UploaderInterface> mock;
    // const char* argv[] = { _program.c_str(), _ip.c_str(), _port.c_str(),
    //                         _filename.c_str(),   "upload",  "vendor", "download" };
    // int argc = sizeof(argv) / sizeof(argv[0]);

    When(Method(mock, connect))
        .AlwaysDo(
            []() {
            });

    When(Method(mock, transfer))
        .AlwaysDo(
            []() {
            });

    When(Method(mock, transfer))
        .AlwaysDo(
            []() {
            });

    When(Method(mock, close))
        .AlwaysDo(
            []() {
            });

    rsi::UploaderInterface& i = mock.get();

    REQUIRE(fs::exists(original));
    i.connect();
    i.transfer();
    i.close();
    REQUIRE(fs::exists(original));
    Verify(Method(mock, connect));
    Verify(Method(mock, transfer));
    Verify(Method(mock, close));

    SystemException::assertion("rm -rf testit;rm -rf testit2;rm -rf runtime;", __INFO__);

}
