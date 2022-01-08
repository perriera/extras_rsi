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

#include <iostream>
#include <extras_rsi/remote/sockets/PortAuthority.hpp>

#include "../../unittesting/catch.hpp"
#include "../../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Dock PortAuthorityInterface", "[PortAuthorityInterface]") {

    int correct_request = 9000;
    Mock<rsi::PortAuthorityInterface> mock;
    When(Method(mock, request)).Return(correct_request);

    rsi::PortAuthorityInterface& i = mock.get();
    REQUIRE(i.request() == correct_request);
    Verify(Method(mock, request));

}
