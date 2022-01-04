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
#include <extras/devices/ansi_colors.hpp>
#include <filesystem>
#include <chrono>
#include <thread>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace std;
using namespace fakeit;
namespace fs = std::filesystem;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

void killAllServers();

SCENARIO("Mock InvocationInterface", "[InvocationInterface]") {

    SystemException::assertion("rm -rf testit; mkdir testit; ", __INFO__);
    SystemException::assertion("cp data/exparx.webflow.zip testit; ", __INFO__);
    SystemException::assertion("cp data/src.zip testit; ", __INFO__);

    auto src_file = "testit/src.zip";
    auto webflow_file = "testit/src.zip";

    const char* argv[] = {
        "build/rsi",
        "127.0.0.1:8080",
        src_file,
        webflow_file
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    // output parameters
    rsi::ServiceTypeList expectedServicesList = {
        "upload 127.0.0.1 9000 data/src.zip",
        "upload 127.0.0.1 9001 data/exparx.webflow.zip",
        "vendor 127.0.0.1 9002 data/src.zip data/exparx.webflow.zip ",
        "download 127.0.0.1 9003 data/src.zip"
    };

    rsi::ParametersX _parameters;
    rsi::ParameterList _parameterList;
    rsi::ParameterList _sentList;
    rsi::ParameterList _receivedList;
    rsi::PortAuthority _portAuthority;
    rsi::ServiceTypeList _serviceTypeList;
    rsi::ServiceTypeList _clientTypeList;
    rsi::ServiceTypeList _serverTypeList;

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
    When(Method(mock, formRequests))
        .AlwaysDo(
            [&_portAuthority](
                const rsi::ParametersInterface& parameters) {
                    rsi::ServiceTypeList serviceTypeList;
                    for (auto filename : parameters.filenames()) {
                        std::stringstream ss;
                        ss << "upload" << ' ' << parameters.address() << ' ';
                        ss << _portAuthority.request() << ' ' << filename;
                        serviceTypeList.push_back(ss.str());
                    }
                    {
                        std::stringstream ss;
                        ss << "vendor" << ' ' << parameters.address() << ' ';
                        ss << _portAuthority.request() << ' ';
                        for (auto filename : parameters.filenames()) {
                            ss << filename << ' ';
                        }
                        serviceTypeList.push_back(ss.str());
                    }
                    {
                        std::stringstream ss;
                        ss << "download" << ' ' << parameters.address() << ' ';
                        ss << _portAuthority.request() << ' ';
                        ss << parameters.filenames()[0];
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
                        if (!rs.isServer(dup[rs.service()]))
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
    When(Method(mock, decompile))
        .AlwaysDo(
            [&i](
                const rsi::ServiceTypeList& before,
                const rsi::ServiceTypeList& after
                ) {
                    for (size_t i = 0; i < before.size(); i++) {
                        auto l1 = before[i];
                        auto l2 = after[i];
                        std::stringstream in1;
                        std::stringstream in2;
                        rsi::RemoteService rs1;
                        rsi::RemoteService rs2;
                        in1 << l1;
                        in1 >> rs1;
                        in2 << l2;
                        in2 >> rs2;
                        if (rs1.service() == "download") {
                            auto src = rs2.filenames()[0];
                            auto des = rs1.filenames()[0];
                            auto cpCmd = "cp " + src + " " + des + " ";
                            SystemException::assertion(cpCmd, __INFO__);
                            std::cout << white << cpCmd << yellow << " rsi update successful" << std::endl;
                        };
                    }
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
            [&_parameterList, &i, &lbi, &_parameters](int socket) {
                if (socket == -2)
                    throw rsi::RSIException("unknown", __INFO__);
                // --- core code below ----
                auto params = _parameters.parameters();
                lbi.send_line_block(params);
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
            [&_parameterList, &i, &_sentList, &_receivedList, &lbi, &_serverTasks](int) {

                auto request = lbi.read_line_block();
                rsi::ParametersX parameters(request);
                auto serviceList = i.formRequests(parameters);

                rsi::Session _serverSession;
                _serverSession.create();

                auto servers = i.compile(_serverTasks, _serverSession, serviceList);
                for (std::string task : servers) {
                    std::cout << task << std::endl;
                    SystemException::assertion(task + " &", __INFO__);
                }

                auto response = i.package_request(serviceList);
                lbi.send_line_block(response);
                return response;

            });

    // 
    // step 0. killAllServers();
    //
    killAllServers();

    When(Method(mock, invoke))
        .AlwaysDo(
            [&i, &lbi, &_clientTasks](const rsi::SessionInterface& session, const rsi::ServiceTypeList& list) {
                // --- core code below ----
                auto clients = i.compile(_clientTasks, session, list);
                for (std::string task : clients) {
                    std::cout << task << std::endl;
                    SystemException::assertion(task, __INFO__);
                }
                i.decompile(list, clients);
            });

    // 
    // step 1. determine, (and validate) parameters
    //
    REQUIRE(_parameterList.size() == 0);
    _parameters.parse(argc, argv);

    for (int attempt = 0; attempt < 3; attempt++) {
        auto servicesList = i.servicesRequest(-1);
        rsi::Session _clientSession;
        _clientSession.create();
        try {
            i.invoke(_clientSession, servicesList);
            _clientSession.destroy();
            break;
        }
        catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
            _clientSession.destroy();
        }
    }

    REQUIRE(fs::exists(src_file));
    REQUIRE(fs::exists(webflow_file));

}
