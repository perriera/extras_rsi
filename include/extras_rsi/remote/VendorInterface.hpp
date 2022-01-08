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

#ifndef _EXPARX_RSI_VENDORINTERFACE_HPP
#define _EXPARX_RSI_VENDORINTERFACE_HPP

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
#include <extras_rsi/remote/ParametersInterface.hpp>
#include <extras_rsi/remote/SessionType.hpp>
#include <extras_rsi/sockets/LineBlock.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief VendorInterface
         *
         * This interface essentially takes into consideration
         * the files to uploaded, processed and downloaded by first
         * consulting with a socket pool server and then creating
         * the actual commands that can be executed on either the
         * server or client portion of the RSI request.
         *
         */
        interface VendorInterface {

            /**
             * @brief clientTasks()
             *
             * Returns a cross table to client exeutables
             * @return const ServiceTypeMap&
             */
            virtual const ServiceTypeMap& clientTasks() pure;

            /**
             * @brief serverTasks()
             *
             * Returns a cross table to server exeutables
             * @return const ServiceTypeMap&
             */
            virtual const ServiceTypeMap& serverTasks() pure;

            /**
             * @brief compile()
             *
             * Once feeback is received from the server, (typically what port have
             * been allocated for each command), create either the client or the
             * server version of the command. Along with formatting the actual command
             * any preparations on the files are performed here.
             *
             * @param serviceTypes
             * @param session
             * @param list
             * @return ServiceTypeList
             */
            virtual ServiceTypeList compile(
                const ServiceTypeMap& serviceTypes,
                const SessionInterface& session,
                const ServiceTypeList& list
            ) const pure;

            /**
             * @brief decompile()
             *
             * Once the compiler is completed and the commands have been executed, the
             * next thing to do is clean up from the commands.
             *
             * @param before
             * @param after
             */
            virtual void decompile(
                const ServiceTypeList& before,
                const ServiceTypeList& after
            ) const pure;

            /**
             * @brief resolve()
             *
             * Take the parameters and apply them to upload, vendor and downloaded versions
             * that can be processed by the client and the server.
             *
             * @param parameters
             * @return ServiceTypeList
             */
            virtual ServiceTypeList resolve(const ParametersInterface& parameters) pure;

        };

    }
}

#endif // _EXPARX_RSI_VENDORINTERFACE_HPP


