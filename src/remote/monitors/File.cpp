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

#include <extras_rsi/remote/monitors/File.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <thread>

using namespace std;
namespace fs = std::filesystem;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

namespace extras {
    namespace rsi {

        /**
         * @brief cause()
         *
         */
        void FileMonitor::cause() {
            sleep_until(system_clock::now() + seconds(_watchDog));
            if (fs::exists(_pathname))
                effect();
        }

        /**
         * @brief effect()
         *
         */
        void FileMonitor::effect() {
            auto lsCmd = "ls -la " + _pathname;
            SystemException::assertion(lsCmd, __INFO__);
            reset();
        }

        /**
         * @brief reset()
         *
         */
        void FileMonitor::reset() {
            auto rmCmd = "rm " + _pathname;
            SystemException::assertion(rmCmd, __INFO__);
        }

    }  // namespace extras
}

