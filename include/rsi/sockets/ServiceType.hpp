#ifndef _EXPARX_RSISERVICETYPE_HPP
#define _EXPARX_RSISERVICETYPE_HPP

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/exceptions.hpp>
#include <rsi/sockets/PortAuthority.hpp>
#include <iostream>

/**
 * @brief
 *
 */

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


