/**
 * @file ServiceType.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief ServiceTypeCompilerInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSI_REMOTESERVICE_HPP
#define _EXPARX_RSI_REMOTESERVICE_HPP

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
#include <extras_rsi/sockets/Types.hpp>
#include <extras_rsi/sockets/PortAuthority.hpp>
#include <extras_rsi/services/SessionType.hpp>
#include <extras_rsi/sockets/LineBlock.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief RemoteServiceInterface
         *
         */

        using ServiceType = std::string;
        using ServiceTypeList = std::vector<std::string>;
        using ServiceTypeMap = std::map<ServiceType, ServiceType>;
        using Parameter = std::string;
        using ParameterList = std::vector<std::string>;

        interface RemoteServiceInterface {
            virtual void parameters(int argc, char const* argv[]) pure;
            virtual Parameter address() const pure;
            virtual Parameter port() const pure;
            virtual Filenames filenames() const pure;
            virtual Pathname shadow(const Pathname& parameter, const SessionInterface& session) pure;
            virtual ServiceTypeList formRequests(const ParameterList& list) pure;
            virtual void formUploads(const ServiceType& type, const SessionInterface& session) pure;
            virtual void formVendor(const ServiceType& type, const SessionInterface& session) pure;
            virtual void formDownloads(const ServiceType& type, const SessionInterface& session) pure;
            virtual ServiceTypeList compile(const ServiceTypeMap& serviceTypes, const SessionInterface& session) pure;
            virtual ServiceTypeList compileClients(const SessionInterface& session) pure;
            virtual ServiceTypeList compileServers(const SessionInterface& session) pure;
            virtual LinePacket package_request(const ServiceTypeList& list) pure;
            virtual ServiceTypeList unpackage_response(const LinePacket& package) pure;
            virtual LinePacket servicesResponse(int socket) pure;
            virtual ServiceTypeList servicesRequest(int socket) pure;
            virtual void start_servers_block(const SessionInterface& session, int socket) pure;
            virtual void start_clients_block(const SessionInterface& session, int socket) pure;
            virtual const ServiceTypeMap& client_tasks() const pure;
            virtual const ServiceTypeMap& server_tasks() const pure;
        };


    }
}

#endif // _EXPARX_RSI_REMOTESERVICE_HPP


