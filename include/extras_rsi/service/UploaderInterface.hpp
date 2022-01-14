/**
 * @file Uploader.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief UploaderInterface, Uploader class
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISERVICES_UPLOADERINTERFACE_HPP
#define _EXPARX_RSISERVICES_UPLOADERINTERFACE_HPP

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
#include <extras_rsi/remote/sockets/LineBlock.hpp>
#include <extras_rsi/remote/sockets/FileBlock.hpp>
#include <extras_rsi/service/Parameters.hpp>
#include <extras_rsi/remote/sockets/Types.hpp>
#include <extras_rsi/remote/sockets/Semaphores.hpp>
#include <extras/status/help.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {
        /**
         * @brief UploaderInterface
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */

        using UploaderStatus = std::string;

        interface UploaderInterface {

            /**
             * @brief connect()
             * @note do whatever socket connection is required, (using the parameters
             * collected earlier)
             */
            virtual void connect() pure;

            /**
             * @brief transfer()
             * @note this is where the magic happens, depending what type of class you
             * are this method performs the data transfer, (or initiates it)
             */
            virtual void transfer() pure;

            /**
             * @brief transfer()
             * @note safely closes all sockets
             */
            virtual void close() const pure;
        };


    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_UPLOADERINTERFACE_HPP
