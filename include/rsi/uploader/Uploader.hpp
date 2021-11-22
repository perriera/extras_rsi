#ifndef _EXPARX_RSISERVICES_UPLOADER_HPP
#define _EXPARX_RSISERVICES_UPLOADER_HPP

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
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

        interface UploaderInterface {
            /**
             * @brief parameters()
             * @note collect the parameters required for the Uploader from the
             * tradional C/C++ main() arguments.
             */
            virtual Parameters parameters(int argc, char const* argv[]) pure;
            virtual Parameter program() const pure;
            virtual Parameter filename() const pure;
            virtual Parameter ip() const pure;
            virtual Parameter port() const pure;

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
            virtual void transfer() const pure;

            /**
             * @brief send()
             * @note this is where the magic happens, depending what type of class you
             * are this method performs the data transfer, (or initiates it)
             */
            virtual void send(const Filename& filename) const pure;

            /**
             * @brief write()
             * @note this is where the magic happens, depending what type of class you
             * are this method performs the data transfer, (or initiates it)
             */
            virtual Filename write(const Filename& filename) const pure;

            /**
             * @brief transfer()
             * @note safely closes all sockets
             */
            virtual void close() const pure;
        };

        /**
         * @brief abstract class Uploader
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */
        abstract class Uploader implements UploaderInterface {
        protected:
            Parameters _parameters;
            struct sockaddr_in _server_addr;
            int _sockfd;

        public:
            virtual Parameters parameters(int argc, char const* argv[]) override;
            virtual Parameter program() const override {
                return _parameters[0];
            };
            virtual Parameter filename() const override {
                return _parameters[1];
            };
            virtual Parameter ip() const override { return _parameters[2]; };
            virtual Parameter port() const override { return _parameters[3]; };

        };

        /**
         * @brief concrete class UploaderClient
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */
        concrete class UploaderClient extends Uploader {
        public:
            virtual void connect() override;
            virtual void transfer() const override;
            virtual void close() const override;
            virtual void send(const Filename& filename) const override;
            virtual Filename write(const Filename& filename) const override;
        };

        /**
         * @brief concrete class UploaderServer
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */
        concrete class UploaderServer extends Uploader {
        protected:
            struct sockaddr_in _new_addr;
            int _new_sock;

        public:
            virtual void connect() override;
            virtual void transfer() const override;
            virtual void close() const override;
            virtual void send(const Filename& filename) const override;
            virtual Filename write(const Filename& filename) const override;
        };


    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_UPLOADER_HPP
