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

SCENARIO("Mock SessionInterface: clients", "[SessionInterface]") {

    extras::Pathname pathname = "data/exparx.webflow.zip";
    rsi::RequestType before = "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip";
    extras::Directory _directory = "/tmp/token";

    Mock<rsi::SessionInterface> mock;
    When(Method(mock, open))
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
    When(Method(mock, close))
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
    // "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip"
    // "vendor 137.184.218.130 9002 /tmp/extras_rsi_PTduD4/src /tmp/extras_rsi_PTduD4/exparx.webflow.zip "

    REQUIRE(!i.exists());
    i.open();
    REQUIRE(i.session() == _directory);
    REQUIRE(i.exists());
    auto fn1 = extras::FileSystem(pathname).filename();
    auto fn2 = extras::FileSystem(_directory).append(fn1);
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
    auto fn3 = extras::FileSystem(_directory).append("/src.zip");
    auto fn4 = extras::FileSystem(_directory).append("/exparx.webflow.zip");
    after += fn3 + " " + fn4 + " ";
    REQUIRE(i.sessionType(before) == after);

    Verify(Method(mock, open));
    Verify(Method(mock, session));
    Verify(Method(mock, close));
    Verify(Method(mock, exists));
    Verify(Method(mock, add));
    Verify(Method(mock, remove));
    Verify(Method(mock, active));

}
