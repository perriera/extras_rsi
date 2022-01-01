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
#include <extras_rsi/services/SessionType.hpp>
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
        "build/uploader_server 137.184.218.130 9000 /tmp/$token/data/src.zip",
        "build/uploader_server 137.184.218.130 9001 /tmp/$token/data/exparx.webflow.zip",
        "build/vendor_server 137.184.218.130 9002 /tmp/$token/data/src.zip /tmp/$token/data/exparx.webflow.zip",
        "build/downloader_server 137.184.218.130 9003 /tmp/$token/data/src.zip",
    };

    extras::Directory _directory;

    Mock<rsi::ServiceTypeCompilerInterface> mock;
    When(Method(mock, common))
        .AlwaysDo(
            [&clients_list](const rsi::ServiceTypeMap& map,
                const rsi::RequestTypeList& requests) {
                    rsi::ServiceTypeList list;
                    rsi::ServiceTypeMap dup = map;
                    for (auto request : requests) {
                        auto parts = extras::split(request, ' ');
                        rsi::NoTokensException::assertion(parts.size(), __INFO__);
                        auto serviceType = dup[parts[0]];
                        rsi::UnsupportedTokenException::assertion(serviceType, __INFO__);
                        std::string line =
                            extras::replace_all(request, parts[0], serviceType);
                        list.push_back(line);
                    }
                    return list;
            });
    rsi::ServiceTypeCompilerInterface& i = mock.get();
    When(Method(mock, clients))
        .AlwaysDo(
            [&i](const rsi::RequestTypeList& requests) {
                rsi::ServiceTypeMap forClients;
                forClients["upload"] = "build/uploader_client";
                forClients["vendor"] = "build/vendor_client";
                forClients["download"] = "build/downloader_client";
                return i.common(forClients, requests);
            });
    When(Method(mock, servers))
        .AlwaysDo(
            [&i, &_directory](const rsi::RequestTypeList& requests) {
                rsi::ServiceTypeMap forServers;
                forServers["upload"] = "build/uploader_server";
                forServers["vendor"] = "build/vendor_server";
                forServers["download"] = "build/downloader_server";
                auto beforeList = i.common(forServers, requests);
                rsi::ServiceTypeList afterList;
                rsi::Session session;
                session.create();
                _directory = session.session();
                afterList = session.sessionTypeList(beforeList);
                return afterList;
            });

    REQUIRE(i.clients(request_list) == clients_list);
    auto afterList = i.servers(request_list);

    rsi::ServiceTypeList updated_servers_list;
    for (auto item : servers_list) {
        auto updated = extras::str::replace_all(item, "/tmp/$token/data", _directory) + " ";
        updated_servers_list.push_back(updated);
    }

    for (size_t i = 0; i < afterList.size(); i++) {
        auto a = afterList[i];
        auto b = updated_servers_list[i];
        REQUIRE(a == b);
    }

    Verify(Method(mock, common));
    Verify(Method(mock, clients));
    Verify(Method(mock, servers));
}
