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

#include <extras_rsi/sockets/Parameters.hpp>
#include <extras_rsi/sockets/SocketPool.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
// 
SCENARIO("Test SocketPoolInterface: new script", "[SocketPoolParameters]") {

    // "/home/perry/Projects/extras_rsi/build/socketpool_client 137.184.218.130 8080 data/exparx.webflow.zip upload vendor download "

    rsi::SocketRequestTypeList _requests = {
        "/home/perry/Projects/extras_rsi/build/socketpool_client",
        "137.184.218.130",
        "8080",
        "data/exparx.webflow.zip",
        "upload",
        "vendor",
        "download"
    };

    rsi::LinePacket linePacket = "upload data/exparx.webflow.zip";
    rsi::LinePacket _sentLine;

    Mock<rsi::LineBlockInterface> lineBlock;
    When(Method(lineBlock, send_line_block))
        .AlwaysDo(
            [&_sentLine](const rsi::LinePacket& linePacket) {
                _sentLine = linePacket;
            });
    When(Method(lineBlock, read_line_block))
        .AlwaysDo(
            [&_sentLine]() {
                return _sentLine;
            });

    rsi::LineBlockInterface& i_lineBlock = lineBlock.get();

    Mock<rsi::SocketPoolInterface> mock;
    When(Method(mock, transfer))
        .AlwaysDo(
            [&_requests, &i_lineBlock]() {


                // i_lineBlock.send_line_block();
                // std::string msg = *this;
                // send_line(msg, this->_client_socket);
                // RequestTypeCompilation compilation;
                // compilation.readSocket(this->_client_socket);
                // auto list = compilation.compilation();
                // for (auto item : clients(list)) {
                //     // cout << "msg received: " << item << endl;
                //     auto cmd = item;
                //     system(cmd.c_str());
                // }
                // std::string cmd = "ls -la " + filename();
                // extras::SystemException::assertion(cmd, __INFO__);
                // std::cout << std::endl;
            });

    rsi::SocketPoolInterface& i = mock.get();
    i.transfer();
    Verify(Method(mock, transfer));
}
