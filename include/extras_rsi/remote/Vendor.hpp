/**
 * @file VendorInterface.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief VendorInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSI_VENDOR_HPP
#define _EXPARX_RSI_VENDOR_HPP

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
#include <extras_rsi/remote/VendorInterface.hpp>
#include <extras_rsi/remote/ParametersX.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief Vendor class
         *
         * This is a standard upload, process and download
         * compilation formula
         *
         */
        class Vendor implements VendorInterface {

        private:

            rsi::PortAuthority& _portAuthority;
            ParametersX _parameters;
            ServiceTypeMap _clientTasks{
                {"upload", "build/uploader_client"},
                {"vendor", "build/vendor_client"},
                {"download", "build/downloader_client"}
            };
            ServiceTypeMap _serverTasks{
                {"upload", "build/uploader_server"},
                {"vendor", "build/vendor_server"},
                {"download", "build/downloader_server"}
            };

        public:

            Vendor(
                rsi::PortAuthority& portAuthority
            ) : _portAuthority(portAuthority) {}

            /**
             * @brief VendorInterface
             *
             */

            virtual const ServiceTypeMap& clientTasks() override { return _clientTasks; }
            virtual const ServiceTypeMap& serverTasks()  override { return _serverTasks; }

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

        };

    }
}

#endif // _EXPARX_RSI_VENDOR_HPP


