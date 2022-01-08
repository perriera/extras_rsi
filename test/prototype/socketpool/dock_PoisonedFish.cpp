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

#include <extras_rsi/prototype/socketpool/PoisonedFish.hpp>
#include <iostream>

#include "../../unittesting/catch.hpp"
#include "../../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Dock PoisonedFishInterface", "[PoisonedFishInterface]") {

    rsi::PoisonedFishKey correct = "1234567890";
    rsi::PoisonedFishKey random = "09887637432";
    Mock<rsi::PoisonedFishInterface> mock;
    When(Method(mock, poisonedFishReceived))
        .AlwaysDo(
            [&correct](const rsi::PoisonedFishKey& msg) {
                return correct == msg;
            });
    When(Method(mock, killServers))
        .AlwaysDo(
            []() {
            });

    rsi::PoisonedFishInterface& i = mock.get();
    REQUIRE(!i.poisonedFishReceived(random));
    REQUIRE(i.poisonedFishReceived(correct));
    i.killServers();
    Verify(Method(mock, poisonedFishReceived));
    Verify(Method(mock, killServers));

    SystemException::assertion("rm -rf testit;rm -rf testit2;", __INFO__);

}
