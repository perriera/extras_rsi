#ifndef _EXPARX_RSIREQUESTTYPE_HPP
#define _EXPARX_RSIREQUESTTYPE_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/sockets/Pool.hpp>
#include <rsi/sockets/PortAuthority.hpp>
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
         * @brief RequestTypeInterface
         *
         * All the types of services that can be run on a remote server.
         *
         */

        interface RequestTypeCompilationInterface {
            friend std::ostream& operator<<(
                std::ostream& out, const RequestTypeCompilationInterface& obj);
            friend std::istream& operator>>(std::istream& in,
                RequestTypeCompilationInterface& obj);
            virtual void setCompilation(const RequestTypeList& list) pure;
            virtual RequestTypeList compilation() const pure;
            virtual void writeSocket(int socket) const pure;
            virtual void readSocket(int socket) pure;
            bool operator==(const RequestTypeCompilationInterface& rhs) const {
                return compilation() == rhs.compilation();
            }

            bool operator!=(const RequestTypeCompilationInterface& rhs) const {
                return !(*this == rhs);
            }
        };

        concrete class RequestTypeCompilation implements
            RequestTypeCompilationInterface {
            RequestTypeList _requestTypeList;

        public:
            RequestTypeCompilation(const RequestTypeList requestTypeList)
                : _requestTypeList(requestTypeList) {}
            RequestTypeCompilation(const std::string& rawString) {
                std::stringstream ss;
                ss << rawString;
            }
            RequestTypeCompilation() {}
            virtual void setCompilation(const RequestTypeList& list) override {
                _requestTypeList = list;
            };
            virtual RequestTypeList compilation() const override {
                return _requestTypeList;
            };
            virtual void writeSocket(int socket) const override;
            virtual void readSocket(int socket) override;
            operator std::string() {
                std::stringstream ss;
                ss << *this;
                return ss.str();
            }
        };

        interface RequestTypeCompilerInterface {
            virtual RequestTypeCompilation compile(
                const ParametersInterface& client,
                PortAuthorityInterface& portAuthority) const pure;
        };

        concrete class RequestTypeCompiler implements RequestTypeCompilerInterface {
        public:
            virtual RequestTypeCompilation compile(
                const ParametersInterface& client,
                PortAuthorityInterface& portAuthority) const override;
            virtual RequestTypeCompilation compile(
                const ParametersInterface& client) const {
                return compile(client, PortAuthority::instance());
            }
        };


    }
}

#endif // _EXPARX_RSIREQUESTTYPE_HPP


