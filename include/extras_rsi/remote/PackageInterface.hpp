/**
 * @file PackageInterface.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief PackageInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSI_PACKAGEINTERFACE_HPP
#define _EXPARX_RSI_PACKAGEINTERFACE_HPP

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
#include <extras_rsi/remote/sockets/LineBlock.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief PackageInterface
         *
         */
        interface PackageInterface {

            /**
             * @brief package_request()
             *
             * Package the request for transport over a socket connection,
             * (typically as a single line). Typically, we replace all std::endl
             * with a semicolon. As long as there are no semicolons used in the
             * message itself, this will work, (see class specific implementation).
             *
             * @param list
             * @return LinePacket
             */
            virtual LinePacket package_request(const ServiceTypeList& list) pure;

            /**
             * @brief unpackage_request()
             *
             * Unpackage the request transported, (see above)
             *
             * @param list
             * @return LinePacket
             */
            virtual ServiceTypeList unpackage_request(const LinePacket& package) pure;
        };

    }
}

#endif // _EXPARX_RSI_PACKAGEINTERFACE_HPP


