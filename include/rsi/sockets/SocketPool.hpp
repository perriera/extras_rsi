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
 * The above copyright notice and  this permission  notice shall be
 * included in all copies or  substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESSED  OR   IMPLIED,  INCLUDING   BUT  NOT  LIMITED  TO  THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT.  IN  NO  EVENT  SHALL EXPARX  INCORPORATED
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER  IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM, OUT  OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR  OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Except  as  contained  in this  notice, the  name of  the EXPARX
 * INCORPORATED shall not  be used in  advertising or  otherwise to
 * promote the sale, use or other dealings in this Software without
 * prior written authorization from EXPARX INCORPORATED.
 *
 * exparx.com and www.exparx.com  are domain names  registered with
 * EXPARX INCORPORATED, (other GPL-themed licenses are included).
 *
 */

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

        /**
         * @brief class SocketPool
         *
         */
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


