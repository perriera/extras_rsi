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

#ifndef _EXPARX_RSIREQUESTTYPE_HPP
#define _EXPARX_RSIREQUESTTYPE_HPP

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/sockets/PortAuthority.hpp>
#include <iostream>

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

        /**
         * @brief RequestTypeCompilerInterface
         *
         */

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


