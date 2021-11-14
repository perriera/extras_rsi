#ifndef _EXPARX_RSISERVICES_VENDER_HPP
#define _EXPARX_RSISERVICES_VENDER_HPP

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/uploader/Uploader.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {
        /**
         * @brief VendorInterface
         * @note at this point the file in question to be operated on has
         * now been successfully uploaded to the server and it is up to
         * the vendor to do something withit. As soon as this method
         * completes the file specifed under filename is considered
         * changed and will be automatically downloaded back to the client.
         * For simplicity, the same filename will be used. This makes it
         * easier for the support system to remove the file as soon as it
         * has been successfully downloaded back to the client.
         *
         */

        interface VendorInterface {

            /**
             * @brief add_value()
             * @param filename
             */
            virtual Parameter parcel() const pure;

            virtual void wrapParcel() pure;
            virtual void deliverParcel() pure;
            virtual void unwrapParcel() pure;

        };

        /**
         * @brief Vendor
         *
         */

        abstract class Vendor implements VendorInterface with UploaderInterface {

        protected:

            rsi::UploaderInterface& _proxy;

            Vendor(rsi::UploaderInterface& proxy) :_proxy(proxy) {}

        public:

            /**
             * @brief add_value()
             * @param filename
             */
            virtual void wrapParcel() override;
            virtual void deliverParcel() override;
            virtual void unwrapParcel() override;

            virtual Parameters parameters(int argc, char const* argv[]) override {
                return _proxy.parameters(argc, argv);
            }
            virtual const Parameter& program() const override {
                return _proxy.program();
            }
            virtual const Parameter& payload() const override {
                return _proxy.payload();
            }
            virtual Parameter parcel() const override {
                return  _proxy.parcel();
            }
            virtual const Parameter& ip() const override {
                return _proxy.ip();
            }
            virtual const Parameter& port() const override {
                return _proxy.port();
            }

        };

        /**
         * @brief VendorClient
         *
         */
        concrete class VendorClient extends Vendor {

            rsi::UploaderClient _client;

        public:

            VendorClient() :Vendor(_client) {}

            virtual void connect() override;
            virtual void transfer() override;
            virtual void close() override;

        };

        /**
         * @brief VendorServer
         *
         */
        concrete class VendorServer extends Vendor {

            rsi::UploaderServer _server;

        public:

            VendorServer() :Vendor(_server) {}

            virtual void connect() override;
            virtual void transfer() override;
            virtual void close() override;

        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_VENDER_HPP
