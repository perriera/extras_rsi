/**
 * @file ServiceType.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief InvocationInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSI_INVOCATION_HPP
#define _EXPARX_RSI_INVOCATION_HPP

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

#include <extras/interfaces.hpp>
#include <extras_rsi/remote/ServiceInterface.hpp>
#include <extras_rsi/sockets/Types.hpp>
#include <extras_rsi/sockets/PortAuthority.hpp>
#include <extras_rsi/services/SessionType.hpp>
#include <extras_rsi/sockets/LineBlock.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief InvocationInterface
         *
         */
        interface InvocationInterface {

            virtual void parse(int argc, char const* argv[]) pure;
            virtual Parameter parameters() const pure;
            virtual const Parameter& address() const pure;
            virtual const Parameter& port() const pure;
            virtual const Filenames& filenames() const pure;

            virtual LinePacket servicesResponse(int socket) pure;
            virtual ServiceTypeList servicesRequest(int socket) pure;

            virtual LinePacket package_request(const ServiceTypeList& list) pure;
            virtual ServiceTypeList unpackage_request(const LinePacket& package) pure;

            virtual ServiceTypeList compile(
                const ServiceTypeMap& serviceTypes,
                const SessionInterface& session,
                const ServiceTypeList& list
            ) const pure;

            virtual ServiceTypeList formRequests(const ParameterList& list) pure;

            virtual void start_servers_block(const SessionInterface& session, int socket) pure;
            virtual void start_clients_block(const SessionInterface& session, int socket) pure;

        };

        /**
         * @brief Invocation class
         *
         */
        concrete class Invocation implements InvocationInterface with LineBlockInterface {
            ParameterList _parameterList;
            Parameter _address;
            Parameter _port;
            Filenames _filenames;
            rsi::PortAuthority& _portAuthority;
            int _client_socket = -1;
            const rsi::ServiceTypeMap& _clientTasks;
            const rsi::ServiceTypeMap& _serverTasks;
            ServiceTypeList _servicesList;

            /**
             * @brief LineBlockInterface implementation
             *
             */
            virtual void send_line_block(const LinePacket& msg) const override;
            virtual LinePacket read_line_block() override;

        public:

            /**
             * @brief Construct a new Invocation object
             *
             * @param portAuthority
             */
            Invocation(
                rsi::PortAuthority& portAuthority,
                const rsi::ServiceTypeMap& clientTasks,
                const rsi::ServiceTypeMap& serverTasks)
                : _portAuthority(portAuthority),
                _clientTasks(clientTasks),
                _serverTasks(serverTasks) {}

            /**
             * @brief InvocationInterface implementation
             *
             */
            virtual void parse(int argc, char const* argv[]) override;
            virtual Parameter parameters() const override;
            virtual  const Parameter& address() const override { return _address; }
            virtual  const Parameter& port() const override { return _port; }
            virtual  const Filenames& filenames() const override { return _filenames; }

            virtual ServiceTypeList servicesRequest(int socket) override;
            virtual LinePacket servicesResponse(int socket) override;

            virtual LinePacket package_request(const ServiceTypeList& list) override;
            virtual ServiceTypeList unpackage_request(const LinePacket& package) override;

            virtual ServiceTypeList compile(
                const ServiceTypeMap& serviceTypes,
                const SessionInterface& session,
                const ServiceTypeList& list
            ) const override;

            virtual ServiceTypeList formRequests(const ParameterList& list) override;

            virtual void start_servers_block(const SessionInterface& session, int socket) override;
            virtual void start_clients_block(const SessionInterface& session, int socket) override;
        };


    }
}

#endif // _EXPARX_RSI_INVOCATION_HPP


