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

#include <extras_rsi/service/downloader/Client.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras_rsi/remote/sockets/DeadmanSwitch.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>

using namespace  extras;

int main(int argc, char const* argv[]) {
    activate_deadman_switch(argv[0]);
    auto code = extras::rsi::downloader_client(argc, argv);
    deactivate_deadman_switch(argv[0]);
    return code;
}
