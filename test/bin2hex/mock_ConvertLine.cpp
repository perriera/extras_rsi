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

#include <rsi/bin2hex/ConvertLine.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock ConvertLineInterface", "[ConvertInterface]") {

    Mock<rsi::ConvertLineInterface> mock;
    When(Method(mock, hexToBin))
        .AlwaysDo(
            [](const rsi::HexLine& hexLine) {
                rsi::BinLine binLine = rsi::hexToBytes(hexLine);
                return binLine;
            });
    When(Method(mock, binToHex))
        .AlwaysDo(
            [](const rsi::BinLine& binLine) {
                rsi::HexLine hexLine = rsi::bytesToHex(binLine);
                return hexLine;
            });

    rsi::ConvertLineInterface& i = mock.get();
    rsi::BinLine binLine = { 'a', 'b', 'c' };
    rsi::HexLine hexLine = i.binToHex(binLine);
    REQUIRE(i.hexToBin(hexLine) == binLine);
    REQUIRE(i.binToHex(binLine) == hexLine);
    Verify(Method(mock, hexToBin));
    Verify(Method(mock, binToHex));
}
