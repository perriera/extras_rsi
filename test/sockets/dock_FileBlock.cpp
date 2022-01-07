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

#include <extras_rsi/sockets/FileBlock.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Test FileBlockInterface: new script2", "[SocketPoolParameters]") {

    rsi::FilePacket filePacket = "upload data/exparx.webflow.zip";
    rsi::FilePacket _sentFile;

    Mock<rsi::FileBlockInterface> mock;
    When(Method(mock, send_file_block))
        .AlwaysDo(
            [&_sentFile](const rsi::FilePacket& filePacket) {
                _sentFile = filePacket;
            });
    When(Method(mock, write_file_block))
        .AlwaysDo(
            [&_sentFile](const rsi::FilePacket&) {
                return _sentFile;
            });

    rsi::FileBlockInterface& i = mock.get();
    i.send_file_block(filePacket);
    REQUIRE(i.write_file_block(filePacket) == filePacket);
    Verify(Method(mock, send_file_block));
    Verify(Method(mock, write_file_block));
}
