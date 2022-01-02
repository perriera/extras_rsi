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

#include <extras_rsi/remote/InvocationInterface.hpp>
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

            send_line_block(parameters());
            auto linePacket = read_line_block();
            _servicesList = unpackage_request(linePacket);
            return _servicesList;
        }

        /**
         * @brief servicesResponse()
         *
         * @param socket
         * @return LinePacket
         */
        LinePacket Invocation::servicesResponse(int socket) {

            _client_socket = socket;

            std::string linePacket;
            while (linePacket.size() == 0) linePacket = read_line_block();
            if (linePacket.size() == 0) throw std::string("test exception");

            rsi::ParametersX parameters(linePacket);
            _servicesList = formRequests(parameters);
            linePacket = package_request(_servicesList);
            send_line_block(linePacket);

            return linePacket;
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
         * @brief formRequests()
         *
         * @param list
         * @return ServiceTypeList
         */
        ServiceTypeList Invocation::formRequests(const ParametersInterface& parameters) {
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
         * @brief runClients()
         *
         * @param session
         * @param socket
         */
        void Invocation::runClients(const SessionInterface& session) {
            auto clients = compile(_clientTasks, session, _servicesList);
            for (std::string task : clients) {
                std::cout << task << std::endl;
                SystemException::assertion(task, __INFO__);
            }
        }

        /**
         * @brief start_clients_block()
         *
         * @param session
         * @param socket
         */
        void Invocation::start_clients_block(const SessionInterface& session) {
            auto clients = compile(_clientTasks, session, _servicesList);
            for (auto task : clients) {
                std::cout << task << std::endl;
            }
        }


    }  // namespace rsi
}  // namespace extras
