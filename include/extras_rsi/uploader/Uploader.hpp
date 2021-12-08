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
#include <extras_rsi/sockets/LineBlock.hpp>
#include <extras_rsi/sockets/FileBlock.hpp>
#include <extras_rsi/uploader/Parameters.hpp>
#include <extras_rsi/sockets/Types.hpp>
#include <extras_rsi/sockets/Semaphores.hpp>
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
            with FileBlockInterface
            with HelpInterface {
        protected:
            Parameters _parameters;
            Parameters _extra_files;
            struct sockaddr_in _server_addr;
            int _sockfd;
            void getHelp(Parameter howto_filename) const;

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

            virtual void  help() const {
                getHelp("HOWTO-upload.md");
            }
        };

        /**
         * @brief concrete class UploaderClient
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */
        concrete class UploaderClient extends Uploader with virtual SemaphoreInterface {
        protected:
            std::string client_dir = "data/client/";

            virtual Lock lock(const Lock& lock)  override;
            virtual Lock unlock(const Lock& lock)  override;
        public:
            virtual void connect() override;
            virtual void transfer() override;
            virtual void close() const override;
            virtual void send_file_block(const Filename& filename) const override;
            virtual Filename write_file_block(const Filename& filename) const override;
            virtual void send_line_block(const LinePacket& msg) const override;
            virtual LinePacket read_line_block() override;
        };

        /**
         * @brief concrete class UploaderServer
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */
        concrete class UploaderServer extends Uploader with virtual SemaphoreInterface {

        protected:
            std::string server_dir = "data/server/";
            struct sockaddr_in _new_addr;
            int _new_sock;

            virtual Lock lock(const Lock& lock)  override;
            virtual Lock unlock(const Lock& lock)  override;
        public:
            virtual void connect() override;
            virtual void transfer() override;
            virtual void close() const override;
            virtual void send_file_block(const FilePacket& filename) const override;
            virtual FilePacket write_file_block(const FilePacket& filename) const override;
            virtual void send_line_block(const UploaderStatus& msg) const override;
            virtual UploaderStatus read_line_block()  override;
        };


    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_UPLOADER_HPP
