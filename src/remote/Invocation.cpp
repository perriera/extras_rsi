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
            extras::rsi::send_line(msg, this->_portAuthority.serversocketport());
        }

        /**
         * @brief read_line_block()
         *
         * @return LinePacket
         */
        LinePacket  Invocation::read_line_block() {
            return extras::rsi::read_line(this->_portAuthority.serversocketport());
        }

        /**
         * @brief parameters()
         *
         * @param argc
         * @param argv
         */
        void Invocation::parameters(int argc, char const* argv[]) {
            rsi::NotEnoughParametersException::assertion(argc, 3, __INFO__);
            rsi::ParameterList _parameterList;
            for (auto i = 1; i < argc; i++)
                _parameterList.push_back(argv[i]);
            for (auto i = 2; i < argc; i++)
                _filenames.push_back(argv[i]);
            _address = extras::str::split(_parameterList[0], ':')[0];
            _port = extras::str::split(_parameterList[0], ':')[1];
        }

        /**
         * @brief servicesRequest()
         *
         * @param socket
         * @return LinePacket
         */
        ServiceTypeList Invocation::servicesRequest(int socket) {
            std::stringstream ss;
            send_line_block(ss.str());
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
            auto linePacket = read_line_block();
            rsi::ParameterList _receivedList;
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
            _servicesList = formRequests(_receivedList);
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
        ServiceTypeList Invocation::formRequests(const ParameterList& list) {
            rsi::ServiceTypeList serviceTypeList;
            for (auto filename : filenames()) {
                std::stringstream ss;
                ss << "upload" << ' ' << address() << ' ';
                ss << _portAuthority.request() << ' ' << filename;
                serviceTypeList.push_back(ss.str());
            }
            {
                std::stringstream ss;
                ss << "vendor" << ' ' << address() << ' ';
                ss << _portAuthority.request() << ' ';
                for (auto filename : filenames()) {
                    ss << filename << ' ';
                }
                serviceTypeList.push_back(ss.str());
            }
            {
                std::stringstream ss;
                ss << "download" << ' ' << address() << ' ';
                ss << _portAuthority.request() << ' ';
                ss << filenames()[0];
                serviceTypeList.push_back(ss.str());
            }
            return serviceTypeList;
        }

        /**
         * @brief start_servers_block()
         *
         * @param session
         * @param socket
         */
        void Invocation::start_servers_block(const SessionInterface& session, int socket) {
            auto servers = compile(_serverTasks, session, _servicesList);
            for (std::string task : servers) {
                std::cout << task << std::endl;
                SystemException::assertion(task + " &", __INFO__);
            }
            auto linePacket = package_request(servers);
            send_line_block(linePacket);
        }

        /**
         * @brief start_clients_block()
         *
         * @param session
         * @param socket
         */
        void Invocation::start_clients_block(const SessionInterface& session, int socket) {
            auto clients = compile(_clientTasks, session, _servicesList);
            for (auto task : clients) {
                std::cout << task << std::endl;
            }
        }


    }  // namespace rsi
}  // namespace extras
