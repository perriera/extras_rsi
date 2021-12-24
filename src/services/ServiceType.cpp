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

#include <extras_rsi/socketpool/Client.hpp>
#include <extras_rsi/services/ServiceType.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {


        /**
         * @brief ServiceTypeCompilerVendor::common()
         *
         * @param map
         * @param requests
         * @return ServiceTypeList
         */
        ServiceTypeList ServiceTypeCompilerVendor::common(const ServiceTypeMap& map,
            const RequestTypeList& requests) const {
            rsi::ServiceTypeList list;
            ServiceTypeMap dup = map;
            for (auto request : requests) {
                auto parts = extras::split(request, ' ');
                NoTokensException::assertion(parts.size(), __INFO__);
                auto serviceType = dup[parts[0]];
                UnsupportedTokenException::assertion(serviceType, __INFO__);
                std::string line =
                    extras::replace_all(request, parts[0], serviceType);
                list.push_back(line);
            }
            return list;
        }

        /**
         * @brief clients()
         *
         * @param requests
         * @return ServiceTypeList
         */
        ServiceTypeList ServiceTypeCompilerVendor::clients(
            const RequestTypeList& requests) const {
            rsi::ServiceTypeMap forClients;
            forClients["upload"] = "build/uploader_client";
            forClients["vendor"] = "build/vendor_client";
            forClients["download"] = "build/downloader_client";
            return common(forClients, requests);
        }

        /**
         * @brief servers()
         *
         * @param requests
         * @return ServiceTypeList
         */
        ServiceTypeList ServiceTypeCompilerVendor::servers(
            const RequestTypeList& requests) const {
            rsi::ServiceTypeMap forServers;
            forServers["upload"] = "build/uploader_server";
            forServers["vendor"] = "build/vendor_server";
            forServers["download"] = "build/downloader_server";
            auto beforeList = common(forServers, requests);
            rsi::ServiceTypeList afterList;
            rsi::Session session;
            session.open();
            afterList = session.sessionTypeList(beforeList);
            return afterList;
        }

        /**
         * @brief isParameter()
         *
         * @param requestType
         * @return true
         * @return false
         */
        bool ServiceTypeCompilerVendor::isParameter(const RequestType& requestType) const {
            auto result = std::find(_serviceList.begin(), _serviceList.end(), requestType);
            return result == _serviceList.end();
        }

    }  // namespace rsi
}  // namespace extras
