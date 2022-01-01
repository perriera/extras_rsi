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

#include <extras_rsi/remote/InvocationInterface.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

void killAllServers();

SCENARIO("Mock InvocationInterface", "[InvocationInterface]") {

    const char* argv[] = {
        "build/rsi",
        "127.0.0.1:8080",
        "data/src.zip",
        "data/exparx.webflow.zip"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    // output parameters
    rsi::ServiceTypeList expectedServicesList = {
        "upload 127.0.0.1 9000 data/src.zip",
        "upload 127.0.0.1 9001 data/exparx.webflow.zip",
        "vendor 127.0.0.1 9002 data/src.zip data/exparx.webflow.zip ",
        "download 127.0.0.1 9003 data/src.zip"
    };

    rsi::ParameterList _parameterList;
    rsi::ParameterList _sentList;
    rsi::ParameterList _receivedList;
    rsi::PortAuthority _portAuthority;
    rsi::ServiceTypeList _serviceTypeList;
    rsi::ServiceTypeList _clientTypeList;
    rsi::ServiceTypeList _serverTypeList;
    extras::Filenames _filenameList;

    rsi::ServiceTypeMap _clientTasks;
    _clientTasks["upload"] = "build/uploader_client";
    _clientTasks["vendor"] = "build/vendor_client";
    _clientTasks["download"] = "build/downloader_client";

    rsi::ServiceTypeMap _serverTasks;
    _serverTasks["upload"] = "build/uploader_server";
    _serverTasks["vendor"] = "build/vendor_server";
    _serverTasks["download"] = "build/downloader_server";

    rsi::LinePacket linePacket = "upload data/exparx.webflow.zip";
    rsi::LinePacket _sentLine;

    Mock<rsi::LineBlockInterface> mock_lbi;
    When(Method(mock_lbi, send_line_block))
        .AlwaysDo(
            [&_sentLine](const rsi::LinePacket& linePacket) {
                _sentLine = linePacket;
            });
    When(Method(mock_lbi, read_line_block))
        .AlwaysDo(
            [&_sentLine]() {
                return _sentLine;
            });

    rsi::LineBlockInterface& lbi = mock_lbi.get();
    lbi.send_line_block(linePacket);
    REQUIRE(lbi.read_line_block() == linePacket);
    Verify(Method(mock_lbi, send_line_block));
    Verify(Method(mock_lbi, read_line_block));

    Mock<rsi::InvocationInterface> mock;
    rsi::InvocationInterface& i = mock.get();
    When(Method(mock, parameters))
        .AlwaysDo(
            [&_parameterList, &_filenameList](int argc, char const* argv[]) {
                rsi::NotEnoughParametersException::assertion(argc, 3, __INFO__);
                for (auto i = 1; i < argc; i++)
                    _parameterList.push_back(argv[i]);
                for (auto i = 2; i < argc; i++)
                    _filenameList.push_back(argv[i]);
            });
    When(Method(mock, address))
        .AlwaysDo(
            [&_parameterList, &i]() {
                return extras::str::split(_parameterList[0], ':')[0];
            });
    When(Method(mock, port))
        .AlwaysDo(
            [&_parameterList, &i]() {
                return extras::str::split(_parameterList[0], ':')[1];
            });
    When(Method(mock, filenames))
        .AlwaysDo(
            [&_parameterList, &i, &_filenameList]() {
                return _filenameList;
            });
    When(Method(mock, formRequests))
        .AlwaysDo(
            [&_portAuthority, &i](
                const rsi::ParameterList&) {
                    rsi::ServiceTypeList serviceTypeList;
                    for (auto filename : i.filenames()) {
                        std::stringstream ss;
                        ss << "upload" << ' ' << i.address() << ' ';
                        ss << _portAuthority.request() << ' ' << filename;
                        serviceTypeList.push_back(ss.str());
                    }
                    {
                        std::stringstream ss;
                        ss << "vendor" << ' ' << i.address() << ' ';
                        ss << _portAuthority.request() << ' ';
                        for (auto filename : i.filenames()) {
                            ss << filename << ' ';
                        }
                        serviceTypeList.push_back(ss.str());
                    }
                    {
                        std::stringstream ss;
                        ss << "download" << ' ' << i.address() << ' ';
                        ss << _portAuthority.request() << ' ';
                        ss << i.filenames()[0];
                        serviceTypeList.push_back(ss.str());
                    }
                    return serviceTypeList;
            });
    When(Method(mock, compile))
        .AlwaysDo(
            [&i](const rsi::ServiceTypeMap& serviceTypes,
                const rsi::SessionInterface& session,
                const rsi::ServiceTypeList& before) {
                    auto dup = serviceTypes;
                    rsi::ServiceTypeList after;
                    for (auto line : before) {
                        std::stringstream in;
                        rsi::RemoteService rs;
                        in << line;
                        in >> rs;
                        rs.prepare(session);
                        std::stringstream out;
                        out << dup[rs.service()] << ' ';
                        out << rs.address() << ' ';
                        out << rs.port() << ' ';
                        for (auto file : rs.filenames())
                            out << session.entry_name(file) << ' ';
                        after.push_back(out.str());
                    }
                    return after;
            });
    When(Method(mock, package_request))
        .AlwaysDo(
            [&_parameterList, &i, &lbi](const rsi::ServiceTypeList& list) {
                std::stringstream ss;
                for (auto param : list)
                    ss << param << ';';
                rsi::LinePacket packet = ss.str();
                return packet;
            });
    When(Method(mock, unpackage_request))
        .AlwaysDo(
            [&_parameterList, &i, &lbi](const rsi::LinePacket& package) {
                auto parts = extras::str::split(package, ';');
                rsi::ServiceTypeList list;
                for (auto item : parts)
                    list.push_back(item);
                return list;
            });
    When(Method(mock, servicesRequest))
        .AlwaysDo(
            [&_parameterList, &i, &lbi](int socket) {
                if (socket == -2)
                    throw rsi::RSIException("unknown", __INFO__);
                // --- core code below ----
                std::stringstream ss;
                for (auto param : _parameterList)
                    ss << param << ' ';
                lbi.send_line_block(ss.str());
                if (socket != -1) { // real time
                    auto linePacket = lbi.read_line_block();
                    auto serviceList = i.unpackage_request(linePacket);
                    return serviceList;
                }
                // --- core code above ----
                else {
                    auto linePacket = i.servicesResponse(-1);
                    auto serviceList = i.unpackage_request(linePacket);
                    return serviceList;
                } // mock
            });
    When(Method(mock, servicesResponse))
        .AlwaysDo(
            [&_parameterList, &i, &_sentList, &_receivedList, &lbi](int) {
                auto linePacket = lbi.read_line_block();
                {
                    std::stringstream ss;
                    ss << linePacket;
                    _receivedList.clear();
                    while (ss.good()) {
                        rsi::Parameter parameter;
                        ss >> parameter;
                        if (ss.good()) _receivedList.push_back(parameter);
                    }
                }
                auto serviceList = i.formRequests(_receivedList);
                linePacket = i.package_request(serviceList);
                lbi.send_line_block(linePacket);
                return linePacket;
            });

    // 
    // step 0. killAllServers();
    //
    killAllServers();

    // 
    // step 1. determine, (and validate) parameters
    //
    REQUIRE(_parameterList.size() == 0);
    i.parameters(argc, argv);

    // 
    // step 2. send/receive parameters
    //

    REQUIRE_THROWS_AS(i.servicesRequest(-2), rsi::RSIException);

    REQUIRE(_sentList != _parameterList);
    auto servicesList = i.servicesRequest(-1);
    REQUIRE(servicesList == expectedServicesList);

    // 
    // step 3. start server requests
    //

    When(Method(mock, start_servers_block))
        .AlwaysDo(
            [&i, &lbi, &_serverTasks, &servicesList](const rsi::SessionInterface& session, int socket) {
                if (socket == -2)
                    throw rsi::RSIException("unknown", __INFO__);
                // --- core code below ----
                auto servers = i.compile(_serverTasks, session, servicesList);
                for (std::string task : servers) {
                    std::cout << task << std::endl;
                    SystemException::assertion(task + " &", __INFO__);
                }
                if (socket != -1) { // real time
                    auto linePacket = i.package_request(servers);
                    lbi.send_line_block(linePacket);
                }
                // --- core code above ----
                else {
                    auto linePacket = i.package_request(servers);
                    lbi.send_line_block(linePacket);
                } // mock

                // --- core code above ----
            });

    rsi::Session _serverSession;
    _serverSession.create();
    i.start_servers_block(_serverSession, -1);

    // 
    // step 4. start client requests
    //

    When(Method(mock, start_clients_block))
        .AlwaysDo(
            [&_parameterList, &i, &servicesList, &_clientTasks](const rsi::SessionInterface& session, int socket) {
                if (socket == -2)
                    throw rsi::RSIException("unknown", __INFO__);
                // --- core code below ----
                auto clients = i.compile(_clientTasks, session, servicesList);
                for (auto task : clients) {
                    std::cout << task << std::endl;
                }
                // --- core code above ----
            });

    rsi::Session _clientSession;
    _clientSession.create();

    // REQUIRE(_parameterList.size() == 3);
    // REQUIRE(i.address() == "127.0.0.1");
    // REQUIRE(i.port() == "8080");
    // i.compile(_serverSession);
    // auto u1 = _serviceTypeList[0];

    Verify(Method(mock, parameters));
}
