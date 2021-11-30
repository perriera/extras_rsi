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

#include <rsi/parcel/Wrap.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock WrapInterface: virgin", "[WrapInterface]") {

    rsi::Parameter before = ~extras::Paths("data/exparx.webflow.zip");
    rsi::Parameter after = extras::replace_all(before, "webflow.zip", "webflow.imploded.zip");
    Mock<rsi::WrapInterface> mock;

    When(Method(mock, wrap))
        .AlwaysDo(
            [&after](const rsi::Filename&) {
                return after;
            });

    When(Method(mock, unWrap))
        .AlwaysDo(
            [&before](const rsi::Filename&) {
                return before;
            });

    rsi::WrapInterface& i = mock.get();
    REQUIRE(i.wrap(before) == after);
    REQUIRE(i.unWrap(after) == before);
    Verify(Method(mock, wrap));
    Verify(Method(mock, unWrap));

}
