#ifndef _EXPARX_RSISOCKETSPOOL_HPP
#define _EXPARX_RSISOCKETSPOOL_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/sockets/Parameters.hpp>
#include <rsi/sockets/Exceptions.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

/**
 * @brief
 *
 */

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
            SocketPoolParametersInterface with ServiceTypeCompilerInterface {
        protected:
            std::string _program;
            std::string _ip;
            std::string _port;
            std::string _filename;
            SocketRequestTypeList _requests;
            SocketRequestTypeList _types;
            SocketRequestTypeMap _lastRequest;

        public:
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
            virtual ServiceTypeList common(ServiceTypeMap& map,
                const RequestTypeList& requests) const {
                rsi::ServiceTypeList list;
                for (auto request : requests) {
                    auto parts = extras::split(request, ' ');
                    NoTokensException::assertion(parts.size(), __INFO__);
                    auto serviceType = map[parts[0]];
                    UnsupportedTokenException::assertion(serviceType, __INFO__);
                    std::string line =
                        extras::replace_all(request, parts[0], serviceType);
                    list.push_back(line);
                }
                return list;
            }
            virtual ServiceTypeList clients(
                const RequestTypeList& requests) const override {
                rsi::ServiceTypeMap forClients;
                forClients["upload"] = "build/uploader_client";
                forClients["download"] = "build/downloader_client";
                return common(forClients, requests);
            }
            virtual ServiceTypeList servers(
                const RequestTypeList& requests) const override {
                rsi::ServiceTypeMap forServers;
                forServers["upload"] = "build/uploader_server";
                forServers["download"] = "build/downloader_server";
                return common(forServers, requests);
            }
        };


    }
}

#endif // _EXPARX_RSISOCKETSPOOL_HPP


