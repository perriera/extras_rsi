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

#ifndef _EXPARX_RSISERVICETYPE_HPP
#define _EXPARX_RSISERVICETYPE_HPP

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
#include <rsi/sockets/Types.hpp>
#include <rsi/exceptions.hpp>
#include <rsi/sockets/PortAuthority.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief ServiceTypeCompilerInterface
         *
         */

        using ServiceType = std::string;
        using ServiceTypeList = std::vector<ServiceType>;
        using ServiceTypeMap = std::map<ServiceType, ServiceType>;

        interface ServiceTypeCompilerInterface {
            virtual ServiceTypeList clients(
                const RequestTypeList& requests) const pure;
            virtual ServiceTypeList servers(
                const RequestTypeList& requests) const pure;
        };

        /**
         * @brief class ServiceTypeCompilerVendor
         *
         */
        concrete class ServiceTypeCompilerVendor  implements ServiceTypeCompilerInterface {
            ServiceTypeList _clients;
            ServiceTypeList _servers;

        protected:
            virtual ServiceTypeList common(ServiceTypeMap& map,
                const RequestTypeList& requests) const {
                rsi::ServiceTypeList list;
                for (auto request : requests) {
                    auto parts = extras::split(request, ' ');
                    NoTokensException::assertion(parts.size(), __INFO__);
                    auto serviceType = map[parts[0]];
                    UnsupportedTokenException::assertion(serviceType, __INFO__);
                    std::string line =
                        extras::replace_all(request, parts[0], serviceType);
                    list.push_back(line);
                }
                return list;
            }
        public:

            virtual ServiceTypeList clients(
                const RequestTypeList& requests) const override {
                rsi::ServiceTypeMap forClients;
                forClients["upload"] = "build/uploader_client";
                forClients["vendor"] = "build/vendor_client";
                forClients["download"] = "build/downloader_client";
                return common(forClients, requests);
            };

            virtual ServiceTypeList servers(
                const RequestTypeList& requests) const override {
                rsi::ServiceTypeMap forServers;
                forServers["upload"] = "build/uploader_server";
                forServers["vendor"] = "build/vendor_server";
                forServers["download"] = "build/downloader_server";
                return common(forServers, requests);
            };
        };

    }
}

#endif // _EXPARX_RSISERVICETYPE_HPP


