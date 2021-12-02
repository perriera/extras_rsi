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
#include <extras_arc/parcel/Wrap.hpp>
#include <extras_arc/parcel.hpp>
#include <extras_arc/parcel/Wrap.hpp>
#include <extras_rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras_arc/imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Mock UploaderInterface: basic2", "[UploaderInterface]") {

    rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    rsi::Parameter _program = "uploader_client";
    rsi::Parameter _filename = original;
    rsi::Parameter _ip = "127.0.0.1";
    rsi::Parameter _port = "8080";

    Mock<rsi::UploaderInterface> mock;
    const char* argv[] = { _program.c_str(), _ip.c_str(), _port.c_str(),
                            _filename.c_str(),   "upload",  "vendor", "download" };
    int argc = 7;

    When(Method(mock, program)).Return(_program);
    When(Method(mock, filename)).Return(_filename);
    When(Method(mock, ip)).Return(_ip);
    When(Method(mock, port)).Return(_port);

    When(Method(mock, parameters))
        .AlwaysDo(
            [](int, char const* []) {
                return rsi::Parameters();
            });

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

    When(Method(mock, send_file_block))
        .AlwaysDo(
            [](const rsi::Filename&) {
            });

    When(Method(mock, write_file_block))
        .AlwaysDo(
            [](const rsi::Filename&) {
                return rsi::Filename();
            });

    When(Method(mock, close))
        .AlwaysDo(
            []() {
            });

    rsi::UploaderInterface& i = mock.get();

    REQUIRE(fs::exists(original));
    REQUIRE(i.parameters(argc, argv) == rsi::Parameters());
    REQUIRE(i.program() == _program);
    REQUIRE(i.filename() == _filename);
    REQUIRE(i.ip() == _ip);
    REQUIRE(i.port() == _port);
    i.connect();
    i.transfer();
    i.send_file_block("filename.txt");
    i.write_file_block("filename.txt");
    i.close();
    REQUIRE(fs::exists(original));
    Verify(Method(mock, parameters));
    Verify(Method(mock, program));
    Verify(Method(mock, filename));
    Verify(Method(mock, ip));
    Verify(Method(mock, connect));
    Verify(Method(mock, transfer));
    Verify(Method(mock, send_file_block));
    Verify(Method(mock, write_file_block));
    Verify(Method(mock, close));
}
