/**
 * @file ServiceType.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief ServiceInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSI_SERVICE_HPP
#define _EXPARX_RSI_SERVICE_HPP

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
#include <extras_rsi/remote/ServiceTypes.hpp>
#include <extras_rsi/sockets/PortAuthority.hpp>
#include <extras_rsi/services/SessionType.hpp>
#include <extras_rsi/sockets/LineBlock.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief PackageInterface
         *
         */
        interface PackageInterface {
            virtual LinePacket package_request(const ServiceTypeList& list) pure;
            virtual ServiceTypeList unpackage_request(const LinePacket& package) pure;
        };

        /**
         * @brief ExecutableInterface
         *
         */
        interface ExecutableInterface {
            virtual void internal(const ServiceType& task) pure;
            virtual void external(const ServiceType& task) pure;
        };

        /**
         * @brief ServiceInterface
         *
         */
        interface ServiceInterface {
            virtual const ServiceType& service() const pure;
            virtual const Parameter& address() const pure;
            virtual const Parameter& port() const pure;
            virtual const Filenames& filenames() const pure;
            virtual bool isUploader() const pure;
            virtual bool isServer(const Parameter& param) const pure;
            virtual void prepare(
                const SessionInterface& session
            ) const pure;
            virtual void cleanup(
                const SessionInterface& session
            ) const pure;
        };

        /**
         * @brief ServicesInterface
         *
         */
        interface ServicesInterface {

            virtual LinePacket servicesResponse(int socket) pure;
            virtual ServiceTypeList servicesRequest(int socket) pure;

        };


    }
}

#endif // _EXPARX_RSI_SERVICE_HPP


