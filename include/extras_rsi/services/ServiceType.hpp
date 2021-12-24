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
#include <extras_rsi/sockets/Types.hpp>
#include <extras_rsi/services/SessionType.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras_rsi/sockets/PortAuthority.hpp>
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

            /**
             * @brief common()
             * @note Common processing between clients and servers_list
             * @param map
             * @param requests
             * @return ServiceTypeList
             */
            virtual ServiceTypeList common(const ServiceTypeMap& map,
                const RequestTypeList& requests) const pure;

            /**
             * @brief clients()
             * @note client specific syntax
             * @param requests
             * @return ServiceTypeList
             */
            virtual ServiceTypeList clients(
                const RequestTypeList& requests) const pure;

            /**
             * @brief servers()
             * @note server specific syntax
             * @param requests
             * @return ServiceTypeList
             */
            virtual ServiceTypeList servers(
                const RequestTypeList& requests) const pure;


            /**
             * @brief isParameter()
             * @note determine if a commandline entry is a parameter, (or not)
             * @param requests
             * @return ServiceTypeList
             */
            virtual bool isParameter(const RequestType& requestType) const pure;
        };

        /**
         * @brief class ServiceTypeCompilerVendor
         *
         */
        concrete class ServiceTypeCompilerVendor  implements ServiceTypeCompilerInterface {
            ServiceTypeList _clients;
            ServiceTypeList _servers;
            ServiceTypeList _serviceList = { "upload","vendor","download" };

        protected:
            virtual ServiceTypeList common(const ServiceTypeMap& map,
                const RequestTypeList& requests) const override;

        public:

            virtual ServiceTypeList clients(
                const RequestTypeList& requests) const override;

            virtual ServiceTypeList servers(
                const RequestTypeList& requests) const override;

            virtual bool isParameter(const RequestType& requestType) const override;

        };

    }
}

#endif // _EXPARX_RSISERVICETYPE_HPP


