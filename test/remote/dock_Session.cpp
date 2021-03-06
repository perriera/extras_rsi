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

SCENARIO("Dock SessionInterface: clients", "[SessionInterface]") {

    extras::Pathname pathname = "data/exparx.webflow.zip";
    rsi::RequestType before = "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip";
    extras::Directory _directory = "/tmp/token";

    Mock<rsi::SessionInterface> mock;
    When(Method(mock, create))
        .AlwaysDo(
            [&_directory]() {
                char templatebuf[80];
                char* mkdirectory = mkdtemp(strcpy(templatebuf, "/tmp/extras_rsi_XXXXXX"));
                std::string tempDir = mkdirectory;
                _directory = tempDir;
            });
    When(Method(mock, session))
        .AlwaysDo(
            [&_directory]() {
                return _directory;
            });
    When(Method(mock, destroy))
        .AlwaysDo(
            [&_directory]() {
                if (_directory != "" && fs::exists(_directory))
                    fs::remove_all(_directory);
            });
    When(Method(mock, exists))
        .AlwaysDo(
            [&_directory]() {
                return _directory != "" && fs::exists(_directory);
            });
    When(Method(mock, entry_name))
        .AlwaysDo(
            [&_directory](const extras::Pathname& entry) {
                auto fn1 = extras::FileSystem(entry).filename();
                auto fn2 = extras::FileSystem(_directory).append(fn1);
                return fn2;
            });
    rsi::SessionInterface& i = mock.get();
    When(Method(mock, add))
        .AlwaysDo(
            [&_directory, &i](const extras::Pathname& entry) {
                if (_directory != "" && fs::exists(_directory)) {
                    auto sessionEntry = i.entry_name(entry);
                    auto cpCmd = "cp " + entry + " " + sessionEntry;
                    SystemException::assertion(cpCmd, __INFO__);
                }
            });
    When(Method(mock, remove))
        .AlwaysDo(
            [&_directory, &i](const extras::Pathname& entry) {
                if (_directory != "" && fs::exists(_directory)) {
                    auto sessionEntry = i.entry_name(entry);
                    if (sessionEntry != "" && fs::exists(sessionEntry))
                        fs::remove(sessionEntry);
                }
            });
    When(Method(mock, active))
        .AlwaysDo(
            [&_directory, &i]() {
                if (_directory != "" && fs::exists(_directory)) {
                    if (_directory != "" && fs::is_directory(_directory)) {
                        return !fs::is_empty(_directory);
                    }
                }
                return false;
            });
    When(Method(mock, sessionType))
        .AlwaysDo(
            [&_directory, &i](const rsi::RequestType& requestType) {
                auto parts = extras::str::split(requestType, ' ');
                rsi::SessionType sessionType;
                for (auto i = 0; i < 3; i++)
                    sessionType += parts[i] + " ";
                for (size_t i = 3; i < parts.size(); i++) {
                    auto fn1 = extras::FileSystem(parts[i]).filename();
                    auto fn2 = extras::FileSystem(_directory).append(fn1);
                    sessionType += fn2 + " ";
                }
                return sessionType;
            });
    When(Method(mock, sessionTypeList))
        .AlwaysDo(
            [&_directory, &i](const rsi::RequestTypeList& beforeList) {
                rsi::ServiceTypeList afterList;
                for (auto before : beforeList) {
                    auto after = i.sessionType(before);
                    afterList.push_back(after);
                }
                return afterList;
            });

    // "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip"
    // "vendor 137.184.218.130 9002 /tmp/extras_rsi_PTduD4/src /tmp/extras_rsi_PTduD4/exparx.webflow.zip "

    REQUIRE(!i.exists());
    i.create();
    REQUIRE(i.session() == _directory);
    REQUIRE(i.exists());
    auto fn1 = extras::FileSystem(pathname).filename();
    auto fn2 = extras::FileSystem(_directory).append(fn1);
    auto correct_answer = fn2;
    REQUIRE(i.entry_name(pathname) == correct_answer);
    REQUIRE(!i.active());
    i.add(pathname);
    REQUIRE(i.active());

    rsi::RequestType after = "vendor 137.184.218.130 9002 ";
    auto fn3 = extras::FileSystem(_directory).append("/src.zip");
    auto fn4 = extras::FileSystem(_directory).append("/exparx.webflow.zip");
    after += fn3 + " " + fn4 + " ";
    REQUIRE(i.sessionType(before) == after);

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

    for (size_t i = 0; i < afterList.size(); i++) {
        auto a = afterList[i];
        auto b = updated_servers_list[i];
        REQUIRE(a == b);
    }

    REQUIRE(afterList == updated_servers_list);

    i.remove(pathname);
    REQUIRE(!i.active());
    i.destroy();
    REQUIRE(!i.exists());
    REQUIRE(!i.active());

    Verify(Method(mock, create));
    Verify(Method(mock, session));
    Verify(Method(mock, destroy));
    Verify(Method(mock, exists));
    Verify(Method(mock, add));
    Verify(Method(mock, remove));
    Verify(Method(mock, active));
    Verify(Method(mock, sessionType));
    Verify(Method(mock, sessionTypeList));

    SystemException::assertion("rm -rf testit;rm -rf testit2;rm -rf runtime;", __INFO__);

}
