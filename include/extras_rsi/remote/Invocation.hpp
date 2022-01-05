/**
 * @file Invocation.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief Invocation class
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
#include <extras_rsi/remote/InvokableInterface.hpp>
#include <extras_rsi/remote/ParametersX.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief Invocation class
         *
         */
        concrete class Invocation implements InvokableInterface
            with ParametersInterface
            with ResolvableInterface
            with ExecutableInterface
            with PackageInterface
            with ServicesInterface
            with LineBlockInterface {
            ParametersX _parameters;
            rsi::PortAuthority& _portAuthority;
            int _client_socket = -1;
            const rsi::ServiceTypeMap& _clientTasks;
            const rsi::ServiceTypeMap& _serverTasks;

            /**
             * @brief LineBlockInterface implementation
             *
             */
            virtual void send_line_block(const LinePacket& msg) const override;
            virtual LinePacket read_line_block() override;

            /**
             * @brief PackageInterface
             *
             * @param list
             * @return LinePacket
             */
            virtual LinePacket package_request(const ServiceTypeList& list) override;
            virtual ServiceTypeList unpackage_request(const LinePacket& package) override;

            /**
             * @brief ResolvableInterface
             *
             */

            virtual ServiceTypeList compile(
                const ServiceTypeMap& serviceTypes,
                const SessionInterface& session,
                const ServiceTypeList& list
            ) const override;

            virtual void decompile(
                const ServiceTypeList& before,
                const ServiceTypeList& after
            ) const override;

            virtual ServiceTypeList resolve(const ParametersInterface& parameters) override;

            /**
             * @brief ExecutableInterface
             *
             * @param task
             */
            virtual void internal(const ServiceType& task) override;
            virtual void external(const ServiceType& task) override;

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
             * @brief ParametersInterface implementation
             *
             */

            virtual void parse(int argc, char const* argv[]) override
            {
                _parameters.parse(argc, argv);
            }

            virtual Parameter parameters() const override {
                return _parameters.parameters();
            }

            virtual const Parameter& address() const override { return _parameters.address(); }
            virtual const Parameter& port() const override { return  _parameters.port(); }
            virtual const Filenames& filenames() const override { return  _parameters.filenames(); }
            virtual ParameterList    list() const override { return  _parameters.list(); }

            /**
             * @brief InvokableInterface implementation
             *
             */

            virtual void invoke(const SessionInterface& session, const ServiceTypeList& list) override;

            /**
             * @brief ServicesInterface
             *
             * @param socket
             * @return ServiceTypeList
             */
            virtual ServiceTypeList servicesRequest(int socket) override;
            virtual LinePacket servicesResponse(int socket) override;

        };


    }
}

#endif // _EXPARX_RSI_INVOCATION_HPP


