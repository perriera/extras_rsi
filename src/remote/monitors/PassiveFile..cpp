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
         * @brief Construct a new Passive File Monitor:: Passive File Monitor object
         *
         * @param pathname
         * @param watchDog
         */
        PassiveFileMonitor::PassiveFileMonitor(const Pathname& pathname, int watchDog)
            :FileMonitor(pathname, watchDog) {
        }

        /**
         * @brief cause()
         *
         */
        void PassiveFileMonitor::cause() {
            auto current = system_clock::now();
            if (current > _timeMarker + seconds(_watchDog)) {
                _timeMarker = current;
                if (fs::exists(_pathname))
                    effect();
            }
        }


    }  // namespace extras
}

