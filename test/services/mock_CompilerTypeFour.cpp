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

#include <extras_rsi/requests/RequestTypeThree.hpp>
#include <extras_rsi/socketpool/Parameters.hpp>
#include <extras_rsi/socketpool/Client.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

// msg received: build/uploader_client 137.184.218.130 9000 data/src.zip
// msg received: build/uploader_client 137.184.218.130 9001 data/exparx.webflow.zip
// msg received: build/vendor_client 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip 
// msg received: build/downloader_client 137.184.218.130 9003 data/src.zip
// msg received: build/uploader_server 137.184.218.130 9000 data/src.zip
// msg received: build/uploader_server 137.184.218.130 9001 data/exparx.webflow.zip
// msg received: build/vendor_server 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip 
// msg received: build/downloader_server 137.184.218.130 9003 data/src.zip

SCENARIO("Mock ServiceTypeCompilerInterface: clients", "[ServiceTypeCompilerInterface]") {

    rsi::RequestTypeList request_list = {
        "upload 137.184.218.130 9000 data/src.zip",
        "upload 137.184.218.130 9001 data/exparx.webflow.zip",
        "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip",
        "download 137.184.218.130 9003 data/src.zip"
    };

    rsi::ServiceTypeList clients_list = {
        "build/uploader_client 137.184.218.130 9000 data/src.zip",
        "build/uploader_client 137.184.218.130 9001 data/exparx.webflow.zip",
        "build/vendor_client 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip",
        "build/downloader_client 137.184.218.130 9003 data/src.zip",
    };

    rsi::ServiceTypeList servers_list = {
        "build/uploader_server 137.184.218.130 9000 data/src.zip",
        "build/uploader_server 137.184.218.130 9001 data/exparx.webflow.zip",
        "build/vendor_server 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip",
        "build/downloader_server 137.184.218.130 9003 data/src.zip",
    };

    Mock<rsi::ServiceTypeCompilerInterface> mock;
    When(Method(mock, clients))
        .AlwaysDo(
            [&clients_list](const rsi::RequestTypeList&) {
                return clients_list;
            });
    When(Method(mock, servers))
        .AlwaysDo(
            [&servers_list](const rsi::RequestTypeList&) {
                return servers_list;
            });

    rsi::ServiceTypeCompilerInterface& i = mock.get();
    REQUIRE(i.clients(request_list) == clients_list);
    REQUIRE(i.servers(request_list) == servers_list);
    Verify(Method(mock, clients));
    Verify(Method(mock, servers));
}
