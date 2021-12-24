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

#include <extras_rsi/socketpool/Client.hpp>
#include <extras_rsi/services/SessionType.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras/filesystem/filesystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>
#include <string.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace rsi {

        /**
         * @brief open()
         *
         */
        void Session::open() {
            char templatebuf[80];
            char* mkdirectory = mkdtemp(strcpy(templatebuf, "/tmp/extras_rsi_XXXXXX"));
            std::string tempDir = mkdirectory;
            _directory = tempDir;
        }

        /**
         * @brief close()
         *
         */
        void Session::close() const {
            if (_directory != "" && fs::exists(_directory))
                fs::remove_all(_directory);
        }

        /**
         * @brief exists()
         *
         * @return true
         * @return false
         */
        bool Session::exists() const {
            return _directory != "" && fs::exists(_directory);
        }

        /**
         * @brief active()
         *
         * @return true
         * @return false
         */
        bool Session::active() const {
            if (_directory != "" && fs::exists(_directory)) {
                if (_directory != "" && fs::is_directory(_directory)) {
                    return !fs::is_empty(_directory);
                }
            }
            return false;
        }

        /**
         * @brief entry_name()
         *
         * @param entry
         * @return extras::Pathname
         */
        extras::Pathname Session::entry_name(const extras::Pathname& entry) const {
            auto fn1 = extras::FileSystem(entry).filename();
            auto fn2 = extras::FileSystem(_directory).append(fn1);
            return fn2;
        }

        /**
         * @brief add()
         *
         * @param entry
         */
        void Session::add(const extras::Pathname& entry) const {
            if (_directory != "" && fs::exists(_directory)) {
                auto sessionEntry = entry_name(entry);
                auto cpCmd = "cp " + entry + " " + sessionEntry;
                SystemException::assertion(cpCmd, __INFO__);
            }
        }

        /**
         * @brief remove()
         *
         * @param entry
         */
        void Session::remove(const extras::Pathname& entry) const {
            if (_directory != "" && fs::exists(_directory)) {
                auto sessionEntry = entry_name(entry);
                if (sessionEntry != "" && fs::exists(sessionEntry))
                    fs::remove(sessionEntry);
            }
        }

        /**
         * @brief sessionType()
         *
         * @param requestType
         * @return SessionType
         */
        SessionType Session::sessionType(const rsi::RequestType& requestType) const {
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
        }

    }  // namespace rsi
}  // namespace extras
