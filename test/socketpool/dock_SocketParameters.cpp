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

#include <extras_rsi/prototype/socketpool/SocketPool.hpp>
#include <extras_rsi/prototype/requests/RequestType.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Dock sockets::ParametersInterface", "[sockets::ParametersInterface]") {

    const char* argv[] = {
        "build/socketpool_client",
        "137.184.218.130",
        "8080",
        "data/src.zip",
        "data/exparx.webflow.zip"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    rsi::Parameters _parameters;
    rsi::Parameter _program;
    rsi::Parameter _ip;
    rsi::Parameter _port;
    rsi::Parameter _filename;
    rsi::SocketRequestTypeList _requests;

    Mock<rsi::sockets::ParametersInterface> mock;
    When(Method(mock, parameters))
        .AlwaysDo(
            [&_parameters, &_program, &_ip, &_port, &_filename, &_requests](int argc, char const* argv[]) {
                if (argc < 4) {
                    std::cout << "params: filename ip port" << std::endl;
                    throw rsi::RSIException("params: filename ip port", __INFO__);
                }
                Parameters copy;
                std::stringstream ss;
                for (int i = 0; i < argc; i++) {
                    ss << argv[i] << ' ';
                    copy.push_back(argv[i]);
                }
                ss >> _program >> _ip >> _port >> _filename;
                _requests.clear();
                while (ss.good()) {
                    rsi::SocketRequestType request;
                    ss >> request;
                    if (ss.good())  _requests.push_back(request);
                }
                return copy;
            });
    When(Method(mock, program))
        .AlwaysDo(
            [&_program]() {
                return _program;
            });
    When(Method(mock, ip))
        .AlwaysDo(
            [&_ip]() {
                return _ip;
            });
    When(Method(mock, port))
        .AlwaysDo(
            [&_port]() {
                return _port;
            });
    When(Method(mock, filename))
        .AlwaysDo(
            [&_filename]() {
                return _filename;
            });
    When(Method(mock, requests))
        .AlwaysDo(
            [&_requests]() {
                return _requests;
            });

    rsi::sockets::ParametersInterface& i = mock.get();
    i.parameters(argc, argv);
    REQUIRE(i.program() == argv[0]);
    REQUIRE(i.ip() == argv[1]);
    REQUIRE(i.port() == argv[2]);
    REQUIRE(i.filename() == argv[3]);
    REQUIRE(i.requests() == _requests);

    Verify(Method(mock, parameters));
    Verify(Method(mock, ip));
    Verify(Method(mock, port));
    Verify(Method(mock, filename));
    Verify(Method(mock, requests));
}
