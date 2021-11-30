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

#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/sockets/Client.hpp>
#include <rsi/sockets/RequestType.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        std::ostream& operator<<(std::ostream& out,
            const RequestTypeCompilationInterface& obj) {
            RequestTypeList list = obj.compilation();
            out << list.size() << endl;
            for (auto line : list) {
                out << line << endl;
            }
            return out;
        }

        std::istream& operator>>(std::istream& in,
            RequestTypeCompilationInterface& obj) {
            int size = 0;
            in >> size;
            RequestType line;
            getline(in, line);
            RequestTypeList list;
            while (size-- > 0 && in.good()) {
                RequestType line;
                getline(in, line);
                if (in.good()) list.push_back(line);
            }
            obj.setCompilation(list);
            return in;
        }

        void RequestTypeCompilation::writeSocket(int socket) const {
            std::stringstream ss;
            ss << *this;
            std::string line = extras::replace_all(ss.str(), "\n", ";");
            send_line(line, socket);
        }
        void RequestTypeCompilation::readSocket(int socket) {
            std::string line = read_line(socket);
            line = extras::replace_all(line, ";", "\n");
            std::stringstream ss;
            ss << line;
            ss >> *this;
        }

        RequestTypeCompilation RequestTypeCompiler::compile(
            const ParametersInterface& client,
            PortAuthorityInterface& portAuthority) const {
            rsi::RequestTypeList list;
            for (auto request : client.requests()) {
                auto port = portAuthority.request();
                std::stringstream ss;
                ss << request << ' ';
                ss << client.filename() << ' ';
                ss << client.ip() << ' ';
                ss << port;
                std::string line = ss.str();
                list.push_back(line);
            }
            return rsi::RequestTypeCompilation(list);
        }

    }  // namespace rsi
}  // namespace extras
