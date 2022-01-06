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

#include <arpa/inet.h>
#include <unistd.h>

#include <extras_rsi/remote/Invocation.hpp>
#include <extras_rsi/remote/Service.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras_rsi/subsystem.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief send_line_block()
         *
         * @param msg
         */
        void  Invocation::send_line_block(const rsi::LinePacket& msg) const {
            extras::rsi::send_line(msg, _client_socket);
        }

        /**
         * @brief read_line_block()
         *
         * @return LinePacket
         */
        LinePacket  Invocation::read_line_block() {
            return extras::rsi::read_line(_client_socket);
        }

        /**
         * @brief servicesRequest()
         *
         * @param socket
         * @return LinePacket
         */
        ServiceTypeList Invocation::servicesRequest(int socket) {
            _client_socket = socket;

            auto params = _parameters.parameters();
            send_line_block(params);
            auto linePacket = read_line_block();
            auto serviceList = unpackage_request(linePacket);
            return serviceList;
        }

        /**
         * @brief servicesResponse()
         *
         * @param socket
         * @return LinePacket
         */
        LinePacket Invocation::servicesResponse(int socket) {
            _client_socket = socket;

            std::string request;
            while (request.size() == 0) request = read_line_block();
            if (request.size() == 0) throw std::string("test exception");

            rsi::ParametersX parameters(request);
            auto serviceList = resolve(parameters);

            rsi::Session _serverSession;
            _serverSession.create();

            auto servers = compile(_serverTasks, _serverSession, serviceList);
            for (std::string task : servers) {
                std::cout << task << std::endl;
                external(task);
            }

            auto response = package_request(serviceList);
            send_line_block(response);

            return response;

        }

        /**
         * @brief package_request()
         *
         * @param list
         * @return LinePacket
         */
        LinePacket Invocation::package_request(const ServiceTypeList& list) {
            std::stringstream ss;
            for (auto param : list)
                ss << param << ';';
            rsi::LinePacket packet = ss.str();
            return packet;
        }

        /**
         * @brief unpackage_request()
         *
         * @param package
         * @return ServiceTypeList
         */
        ServiceTypeList Invocation::unpackage_request(const LinePacket& package) {
            auto parts = extras::str::split(package, ';');
            rsi::ServiceTypeList list;
            for (auto item : parts)
                list.push_back(item);
            return list;
        }

        /**
         * @brief compile()
         *
         * @param serviceTypes
         * @param session
         * @param before
         * @return ServiceTypeList
         */
        ServiceTypeList Invocation::compile(
            const ServiceTypeMap& serviceTypes,
            const SessionInterface& session,
            const ServiceTypeList& before
        ) const {
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
        }

        /**
         * @brief decompile()
         *
         * @param before
         * @param after
         */
        void Invocation::decompile(
            const ServiceTypeList& before,
            const ServiceTypeList& after
        ) const {
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
        }

        /**
         * @brief resolve()
         *
         * @param list
         * @return ServiceTypeList
         */
        ServiceTypeList Invocation::resolve(const ParametersInterface& parameters) {
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
        }

        /**
         * @brief ExecutableInterface
         *
         */
        void Invocation::internal(const ServiceType& task) {
            std::stringstream in;
            rsi::RemoteService rs;
            in << task;
            in >> rs;
            rs.internal(task);
        }
        void Invocation::external(const ServiceType& task) {
            std::stringstream in;
            rsi::RemoteService rs;
            in << task;
            in >> rs;
            rs.external(task);
        }

        /**
         * @brief invoke()
         *
         * @param socket
         */
        void Invocation::invoke(int socket) {

            for (int attempt = 0; attempt < 3; attempt++) {
                auto servicesList = servicesRequest(socket);
                rsi::Session _clientSession;
                _clientSession.create();
                try {

                    // --- core code below ----
                    auto clients = compile(_clientTasks, _clientSession, servicesList);
                    for (std::string task : clients) {
                        std::cout << task << std::endl;
                        external(task);
                    }
                    decompile(servicesList, clients);
                    _clientSession.destroy();

                    break;
                }
                catch (std::exception& ex) {
                    std::cout << red << ex.what() << reset << std::endl;
                    _clientSession.destroy();
                }
            }

        }

        /**
         * @brief service()
         *
         * @param socket
         */
        void Invocation::service(int socket) {
            servicesResponse(socket);
        }


    }  // namespace rsi
}  // namespace extras
