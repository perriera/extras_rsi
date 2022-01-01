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

#include <extras_rsi/socketpool/SocketPool.hpp>
#include <extras_rsi/requests/RequestType.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock SocketPoolInterface", "[SocketPoolInterface]") {

    // input parameters
    rsi::SocketParaneters parameters;
    rsi::PortAuthority portAuthority;
    const char* argv[] = {
        "/home/perry/Projects/extras_rsi/build/socketpool_client",
        "137.184.218.130",
        "8080",
        "data/src.zip",
        "data/exparx.webflow.zip"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);
    parameters.parameters(argc, argv);
    rsi::RequestTypeCompilation _compilation(-1);

    // output parameters
    rsi::ServiceTypeList request_list = {
        "upload 137.184.218.130 9000 data/src.zip",
        "upload 137.184.218.130 9001 data/exparx.webflow.zip",
        "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip",
        "download 137.184.218.130 9003 data/src.zip"
    };

    Mock<rsi::LineBlockInterface> mock_lb;
    When(Method(mock_lb, send_line_block))
        .AlwaysDo(
            [&_compilation](const rsi::LinePacket& msg) {
                _compilation.send_line_block(msg);
            });
    When(Method(mock_lb, read_line_block))
        .AlwaysDo(
            [&_compilation]() {
                rsi::ServiceTypeList request_list = {
                    "upload 137.184.218.130 9000 data/src.zip",
                    "upload 137.184.218.130 9001 data/exparx.webflow.zip",
                    "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip",
                    "download 137.184.218.130 9003 data/src.zip"
                };
                std::string line = extras::replace_all("_line", ";", "\n");
                return line;
            });

    Mock<rsi::ServiceTypeCompilerInterface> mock_stc;
    When(Method(mock_stc, clients))
        .AlwaysDo(
            [](const rsi::RequestTypeList& requests) {
                return rsi::ServiceTypeList();
            });

    rsi::LineBlockInterface& ilb = mock_lb.get();
    rsi::ServiceTypeCompilerInterface& istc = mock_stc.get();

    Mock<rsi::SocketPoolInterface> mock;
    When(Method(mock, transfer))
        .AlwaysDo(
            [&ilb, &parameters, &istc]() {
                // std::string msg = parameters;
                // ilb.send_line_block(msg);
                // rsi::RequestTypeCompilation compilation(-1);
                // compilation.read_line_block();
                // auto list = compilation.compilation();
                // for (auto item : istc.clients(list)) {
                //     // cout << "msg received: " << item << endl;
                //     auto cmd = item;
                //     system(cmd.c_str());
                // }
                // // std::string cmd = "ls -la " + filename();
                // // extras::SystemException::assertion(cmd, __INFO__);
                // std::cout << std::endl;
            });

    rsi::SocketPoolInterface& i = mock.get();
    i.transfer();
    Verify(Method(mock, transfer));
}
