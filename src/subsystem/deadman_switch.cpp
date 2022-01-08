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

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <extras_rsi/gadgets/StatusBar.hpp>
#include <extras_rsi/gadgets/Spinner.hpp>
#include <extras_arc/parcel.hpp>
#include <extras_rsi/sockets/SubSystem.hpp>
#include <extras/strings.hpp>
#include <extras/devices/ansi_colors.hpp>

#include <extras_rsi/remote/InvokableInterface.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <thread>


using namespace extras;
using namespace std;
namespace fs = std::filesystem;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

using namespace std;

namespace extras {

    /**
     * @brief extras_rsi: (remote services interface)
     *
     * The following code has been plagerized from other authors
     * and placed here, (where is/as is) as it is code that works
     * and serves a platform for future work when it comes to
     * uploading files over an IP:port connection.
     *
     */
    namespace rsi {

        bool _dead_man_switch = true;

        void kill_deadman_switch()
        {
            _dead_man_switch = false;
        }

        void deadman_switch(string msg)
        {
            cout << cyan << "deadman_switch activated for: " << green << msg << std::endl;
            sleep_until(system_clock::now() + seconds(15));
            if (_dead_man_switch) {
                cout << std::endl << red << "deadman_switch killed: " << green << msg << std::endl;
                exit(-1);
            }
        }

    }
}

