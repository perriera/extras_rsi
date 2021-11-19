#ifndef _EXPARX_RSISOCKETSPOOL_HPP
#define _EXPARX_RSISOCKETSPOOL_HPP

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Parameters.hpp>
#include <rsi/sockets/ServiceType.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief SocketPoolInterface
         *
         * The idea is that we assign a port to be the authority on deligating
         * available port numbers, (from a range of port numbers). At the basic
         * level a series of predefined tokens are given to this interface. If all
         * tokens are reconized then a port number is returned for each token.
         *
         * The purpose of a token is to inform the SocketPool instance what type of
         * socket service will be expected to be running on that port. Earlier
         * prototypes to this just returned a single port number. However, it was
         * soon realized that perhaps more than one port is required and to inform
         * the socket pool manager in advance of what type of service to running on
         * that port would be advantageous.
         *
         * This version only returns a port number, a more enhanced version would
         * support IP addresses, (hence supporting socket pools over different IPs).
         *
         */

        interface SocketPoolInterface {
            virtual void transfer() const pure;
        };

        abstract class SocketPool implements SocketPoolInterface with
            ParametersInterface with ServiceTypeCompilerInterface {
        protected:
            std::string _program;
            std::string _ip;
            std::string _port;
            std::string _filename;
            SocketRequestTypeList _requests;
            SocketRequestTypeList _types;
            SocketRequestTypeMap _lastRequest;
            const ServiceTypeCompilerInterface& _compilerInterface;

        public:
            SocketPool(const ServiceTypeCompilerInterface& compilerInterface) :_compilerInterface(compilerInterface) {
            }
            virtual Parameters parameters(int argc, char const* argv[]) override;
            virtual const Parameter& program() const override { return _program; };
            virtual const Parameter& ip() const override { return _ip; };
            virtual const Parameter& port() const override { return _port; };
            virtual const Parameter& filename() const override { return _filename; };
            virtual const SocketRequestTypeList& requests() const override {
                return _requests;
            };

            virtual void setProgram(const Parameter& program) override {
                _program = program;
            }
            virtual void setIP(const IP& ip) override { _ip = ip; }
            virtual void setPort(const Port& port) override {
                _port = std::to_string(port);
            }
            virtual void setFilename(const Filename& filename) override {
                _filename = filename;
            }
            virtual void setRequests(const SocketRequestTypeList& list) override {
                _requests = list;
            }

            virtual ServiceTypeList clients(
                const RequestTypeList& requests) const override {
                return _compilerInterface.clients(requests);
            };
            virtual ServiceTypeList servers(
                const RequestTypeList& requests) const override {
                return _compilerInterface.servers(requests);
            };
        };


    }
}

#endif // _EXPARX_RSISOCKETSPOOL_HPP

