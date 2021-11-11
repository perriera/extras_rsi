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
            virtual void addContent(const Filename& filename) pure;
            virtual void changeContent(const Filename& filename) pure;
            virtual void deleteContent(const Filename& filename) pure;

        };

        /**
         * @brief Vendor
         *
         */

        concrete class Vendor implements VendorInterface {

            rsi::UploaderClient _proxy;

        public:

            /**
             * @brief add_value()
             * @param filename
             */
            virtual void addContent(const Filename& filename) override;
            virtual void changeContent(const Filename& filename) override;
            virtual void deleteContent(const Filename& filename) override;
        };

        /**
         * @brief VendorClient
         *
         */
        concrete class VendorClient extends Vendor with UploaderInterface {

            rsi::UploaderClient _proxy;

        public:

            virtual Parameters parameters(int argc, char const* argv[]) override {
                return _proxy.parameters(argc, argv);
            }
            virtual const Parameter& program() const override {
                return _proxy.program();
            }
            virtual const Parameter& filename() const override {
                return _proxy.filename();
            }
            virtual const Parameter& ip() const override {
                return _proxy.ip();
            }
            virtual const Parameter& port() const override {
                return _proxy.port();
            }
            virtual void connect() override {
                addContent(filename());
                return _proxy.connect();
            }
            virtual void transfer()  override {
                return _proxy.transfer();
            }
            virtual void close()  override {
                return _proxy.close();
                deleteContent(filename());
            }

        };

        /**
         * @brief VendorServer
         *
         */
        concrete class VendorServer extends Vendor with UploaderInterface {

            rsi::UploaderServer _proxy;

        public:

            virtual Parameters parameters(int argc, char const* argv[]) override {
                return _proxy.parameters(argc, argv);
            }
            virtual const Parameter& program() const override {
                return _proxy.program();
            }
            virtual const Parameter& filename() const override {
                return _proxy.filename();
            }
            virtual const Parameter& ip() const override {
                return _proxy.ip();
            }
            virtual const Parameter& port() const override {
                return _proxy.port();
            }
            virtual void connect() override {
                _proxy.connect();
            }
            virtual void transfer()  override {
                _proxy.transfer();
                changeContent(filename());
            }
            virtual void close()  override {
                _proxy.close();
            }


        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_VENDER_HPP
