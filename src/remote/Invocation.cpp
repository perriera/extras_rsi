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
            return unpackage_request(linePacket);;
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
            auto _servicesList = resolve(parameters);
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
         * @brief runClients()
         *
         * @param session
         * @param socket
         */
        void Invocation::invoke(const SessionInterface& session, const ServiceTypeList& list) {
            auto clients = compile(_clientTasks, session, list);
            for (std::string task : clients) {
                std::cout << task << std::endl;
                SystemException::assertion(task, __INFO__);
            }
            decompile(list, clients);
        }

        /**
         * @brief ExecutableInterface
         *
         */
        void Invocation::internal(const ServiceType&) {}
        void Invocation::external(const ServiceType&) {}


    }  // namespace rsi
}  // namespace extras
