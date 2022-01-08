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
#include <extras_rsi/remote/sockets/SubSystem.hpp>
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
                    auto clients = compile(clientTasks(), _clientSession, servicesList);
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

            auto servers = compile(serverTasks(), _serverSession, serviceList);
            for (std::string task : servers) {
                std::cout << task << std::endl;
                external(task);
            }

            auto response = package_request(serviceList);
            send_line_block(response);

            return response;

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
