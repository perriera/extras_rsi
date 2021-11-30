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

#include <rsi/sockets/Semaphores.hpp>
#include <rsi/uploader/Uploader.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock SemaphoreInterface: lock/unlock", "[SemaphoreInterface]") {

    Mock<rsi::SemaphoreInterface> sema;
    Mock<rsi::UploaderInterface> uploader;

    rsi::Lock locked = "hello";

    When(Method(sema, lock))
        .AlwaysDo(
            [](const rsi::Lock& lock) {
                return lock;
            });
    When(Method(sema, unlock))
        .AlwaysDo(
            [](const rsi::Lock& lock) {
                return lock;
            });

    rsi::SemaphoreInterface& i_sema = sema.get();

    When(Method(uploader, transfer))
        .AlwaysDo(
            [&i_sema]() {
                rsi::Lock lock;
                i_sema.unlock(i_sema.lock(lock));
            });

    i_sema.lock(i_sema.unlock(locked));
    i_sema.unlock(i_sema.lock(locked));
    Verify(Method(sema, lock));
    Verify(Method(sema, unlock));

    rsi::UploaderInterface& i_uploader = uploader.get();
    i_uploader.transfer();
    Verify(Method(uploader, transfer));


}
