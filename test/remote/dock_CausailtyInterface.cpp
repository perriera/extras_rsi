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

#include <extras_rsi/remote/CausalityInterface.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Dock CausalityInterface", "[CausalityInterface]") {

    bool cause_called = false;
    bool effect_called = false;
    bool reset_called = false;
    Mock<rsi::CausalityInterface> mock;
    rsi::CausalityInterface& i = mock.get();
    When(Method(mock, cause))
        .AlwaysDo(
            [&cause_called, &i]() {
                cause_called = true;
                i.effect();
            });
    When(Method(mock, effect))
        .AlwaysDo(
            [&effect_called, &i]() {
                effect_called = true;
                i.reset();
            });
    When(Method(mock, reset))
        .AlwaysDo(
            [&reset_called, &i]() {
                reset_called = true;
            });

    REQUIRE(!cause_called);
    REQUIRE(!effect_called);
    REQUIRE(!reset_called);
    i.cause();
    REQUIRE(cause_called);
    REQUIRE(effect_called);
    REQUIRE(reset_called);

    Verify(Method(mock, cause));
    Verify(Method(mock, effect));
    Verify(Method(mock, reset));
}
