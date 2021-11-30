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

#ifndef _EXPARX_RSISOCKETSPARAMETERS_HPP
#define _EXPARX_RSISOCKETSPARAMETERS_HPP

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief ParametersInterface
         *
         */

        interface ParametersInterface {
            friend std::ostream& operator<<(std::ostream& out,
                const ParametersInterface& obj);
            friend std::istream& operator>>(std::istream& in,
                ParametersInterface& obj);
            virtual Parameters parameters(int argc, char const* argv[]) pure;
            virtual const Parameter& program() const pure;
            virtual const Parameter& ip() const pure;
            virtual const Parameter& port() const pure;
            virtual const Parameter& filename() const pure;
            virtual const SocketRequestTypeList& requests() const pure;

            virtual void setProgram(const Parameter& program) pure;
            virtual void setIP(const IP& ip) pure;
            virtual void setPort(const Port& port) pure;
            virtual void setFilename(const Filename& filename) pure;
            virtual void setRequests(const SocketRequestTypeList& list) pure;

            bool operator==(const ParametersInterface& rhs) const {
                std::stringstream ssA;
                ssA << *this;
                std::string testA = ssA.str();
                std::stringstream ssB;
                ssB << rhs;
                std::string testB = ssB.str();
                return testB == testA;
            }

            bool operator!=(const ParametersInterface& rhs) const {
                return !(*this == rhs);
            }
        };

    }
}

#endif // _EXPARX_RSISOCKETSPARAMETERS_HPP


