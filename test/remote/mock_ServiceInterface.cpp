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

#include <extras_rsi/remote/ServiceInterface.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock RemoteInvocationInterface", "[RemoteInvocationInterface]") {

    const char* argv[] = {
        "build/rsi",
        "137.184.218.130:8080",
        "data/src.zip",
        "data/exparx.webflow.zip"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    // output parameters
    rsi::ServiceTypeList expectedServicesList = {
        "upload 137.184.218.130 9000 data/src.zip",
        "upload 137.184.218.130 9001 data/exparx.webflow.zip",
        "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip ",
        "download 137.184.218.130 9003 data/src.zip"
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

    Mock<rsi::RemoteInvocationInterface> mock;
    rsi::RemoteInvocationInterface& i = mock.get();
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
    When(Method(mock, shadow))
        .AlwaysDo(
            [](const Pathname& parameter, const rsi::SessionInterface& session) {
                auto result = session.entry_name(parameter);
                return result;
            });
    When(Method(mock, client_tasks))
        .AlwaysDo(
            [&_clientTasks, &i]() {
                return _clientTasks;
            });
    When(Method(mock, server_tasks))
        .AlwaysDo(
            [&_serverTasks, &i]() {
                return _serverTasks;
            });
    When(Method(mock, formRequests))
        .AlwaysDo(
            [&_portAuthority, &i](
                const rsi::ParameterList& list) {
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
    When(Method(mock, formUploads))
        .AlwaysDo(
            [&_parameterList, &_portAuthority, &_serviceTypeList, &i](
                const rsi::ServiceType& serviceType, const rsi::SessionInterface& session) {
                    for (auto filename : i.filenames()) {
                        std::stringstream ss;
                        ss << serviceType << ' ' << i.address() << ' ';
                        ss << _portAuthority.request() << ' ' << session.entry_name(filename);
                        _serviceTypeList.push_back(ss.str());
                    }
            });
    When(Method(mock, formVendor))
        .AlwaysDo(
            [&_parameterList, &_portAuthority, &_serviceTypeList, &i](
                const rsi::ServiceType& serviceType, const rsi::SessionInterface& session) {
                    std::stringstream ss;
                    ss << serviceType << ' ' << i.address() << ' ';
                    ss << _portAuthority.request() << ' ';
                    for (auto filename : i.filenames()) {
                        ss << session.entry_name(filename) << ' ';
                    }
                    _serviceTypeList.push_back(ss.str());
            });
    When(Method(mock, formDownloads))
        .AlwaysDo(
            [&_parameterList, &_portAuthority, &_serviceTypeList, &i](
                const rsi::ServiceType& serviceType, const rsi::SessionInterface& session) {
                    std::stringstream ss;
                    ss << serviceType << ' ' << i.address() << ' ';
                    ss << _portAuthority.request() << ' ' << i.filenames()[0];
                    _serviceTypeList.push_back(ss.str());
            });
    When(Method(mock, compile))
        .AlwaysDo(
            [&i]
    (const rsi::ServiceTypeMap& serviceTypes, const rsi::SessionInterface& session, const rsi::ServiceTypeList& before) {
                auto dup = serviceTypes;
                rsi::ServiceTypeList after;
                for (auto line : before) {
                    std::stringstream in;
                    in << line;
                    rsi::Parameter service, ip, port;
                    in >> service >> ip >> port;
                    rsi::ParameterList files;
                    while (in.good()) {
                        rsi::Parameter file;
                        in >> file;
                        if (file != "")
                            files.push_back(file);
                    }
                    std::stringstream out;
                    out << dup[service] << ' ';
                    out << ip << ' ';
                    out << port << ' ';
                    for (auto file : files)
                        out << session.entry_name(file) << ' ';
                    after.push_back(out.str());
                }
                return after;
            });
    When(Method(mock, prepare))
        .AlwaysDo(
            [&_serviceTypeList, &i](const rsi::SessionInterface& session,
                const rsi::ServiceTypeList& list) {
                    // return i.compile(i.client_tasks(), session, _serviceTypeList);
            });
    When(Method(mock, compileClients))
        .AlwaysDo(
            [&_serviceTypeList, &i](const rsi::SessionInterface& session) {
                return i.compile(i.client_tasks(), session, _serviceTypeList);
            });
    When(Method(mock, compileServers))
        .AlwaysDo(
            [&_serviceTypeList, &i, &_serverTasks](const rsi::SessionInterface& session) {
                return i.compile(_serverTasks, session, _serviceTypeList);
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
    When(Method(mock, unpackage_response))
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
                    auto serviceList = i.unpackage_response(linePacket);
                    return serviceList;
                }
                // --- core code above ----
                else {
                    auto linePacket = i.servicesResponse(-1);
                    auto serviceList = i.unpackage_response(linePacket);
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
    When(Method(mock, start_clients_block))
        .AlwaysDo(
            [&_parameterList, &i](const rsi::SessionInterface& session, int socket) {
                auto list = i.compileClients(session);
                for (auto task : list) {
                    std::cout << task << std::endl;
                }
            });
    When(Method(mock, start_servers_block))
        .AlwaysDo(
            [&_parameterList, &i, &_serverTasks](const rsi::SessionInterface& session, int socket) {
                auto list = i.compileServers(session);
                for (auto task : list) {
                    std::cout << task << std::endl;
                }
            });

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

    rsi::Session _clientSession;
    _clientSession.create();
    rsi::Session _serverSession;
    _serverSession.create();

    auto clients = i.compile(_clientTasks, _clientSession, servicesList);
    auto servers = i.compile(_serverTasks, _serverSession, servicesList);

    i.prepare(_clientSession, clients);
    i.prepare(_serverSession, servers);

    i.start_servers_block(_serverSession, -1);

    // REQUIRE(_parameterList.size() == 3);
    // REQUIRE(i.address() == "137.184.218.130");
    // REQUIRE(i.port() == "8080");
    // i.compile(_serverSession);
    // auto u1 = _serviceTypeList[0];

    Verify(Method(mock, parameters));
}
