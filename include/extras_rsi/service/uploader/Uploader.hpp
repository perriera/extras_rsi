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

#ifndef _EXPARX_RSISERVICES_UPLOADER_HPP
#define _EXPARX_RSISERVICES_UPLOADER_HPP

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
#include <extras_rsi/service/uploader/UploaderInterface.hpp>
#include <extras_rsi/remote/sockets/LineBlock.hpp>
#include <extras_rsi/remote/sockets/FileBlock.hpp>
#include <extras_rsi/service/uploader/Parameters.hpp>
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
         * @brief abstract class Uploader
         *
         * ex.
         *   build/uploader_client data/exparx.webflow.zip 137.184.218.130 8080
         *   ss >> prg >> filename >> ip >> port;
         *
         */
        abstract class Uploader implements UploaderInterface
            with uploader::ParametersInterface
            with LineBlockInterface
            with FileBlockInterface {
        protected:
            Parameters _parameters;
            Parameters _extra_files;
            struct sockaddr_in _server_addr;
            int _sockfd;

        public:
            virtual Parameters parameters(int argc, char const* argv[]) override;
            virtual Parameter program() const override {
                return _parameters[0];
            };
            virtual Parameter filename() const override {
                return _parameters[3];
            };
            virtual Parameter ip() const override {
                return _parameters[1];
            };
            virtual Parameter port() const override {
                return _parameters[2];
            };
            virtual  Parameters extra_files() const override {
                return _extra_files;
            };

        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_UPLOADER_HPP
