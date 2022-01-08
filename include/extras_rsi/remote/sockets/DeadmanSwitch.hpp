/**
 * @file DeadmanSwitch.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief A primative method of stopping an external service
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXTRA_RSIDEADMENSWITCH_HPP
#define _EXTRA_RSIDEADMENSWITCH_HPP

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

#include <extras/interfaces.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#define activate_deadman_switch(msg) std::thread t1(extras::rsi::deadman_switch, msg); t1.detach();
#define deactivate_deadman_switch(msg) extras::rsi::kill_deadman_switch()

namespace extras {

    /**
     * @brief extras_rsi: (remote services interface)
     *
     * A socket connection, (whether across the Internet or across
     * a simple wire connecting to cans), can do down for any reason.
     * This is often manifested as a timeout condition. There is really
     * nothing that can be done but to stop the entire process, (so that
     * another attempt can be made). This is the purpose of the
     * deadman_switch, (it allows a process to terminate itself).
     *
     * Basically, a certain amount of time is given for a task to be executed.
     * If that time is exceeded then the entire task is terminated.
     *
     * Compliments the C/C++ system() function, this works out nicely.
     *
     * This technique cannot be used for internal thread management, (as it
     * is designed to take down the entire program, not just a single thread).
     *
     */
    namespace rsi {

        void deadman_switch(std::string msg);
        void kill_deadman_switch();

    }  // namespace rsi

}  // namespace extras

#endif  // _EXTRA_RSIDEADMENSWITCH_HPP
