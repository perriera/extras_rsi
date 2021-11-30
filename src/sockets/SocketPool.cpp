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

        /**
         * @brief ParametersInterface ostream
         *
         * @param out
         * @param obj
         * @return std::ostream&
         */

        std::ostream& operator<<(std::ostream& out,
            const ParametersInterface& obj) {
            out << obj.program() << ' ';
            out << obj.ip() << ' ';
            out << obj.port() << ' ';
            out << obj.filename() << ' ';
            for (auto request : obj.requests()) out << request << ' ';
            return out;
        }

        /**
         * @brief ParametersInterface istream
         *
         * @param in
         * @param obj
         * @return std::istream&
         */
        std::istream& operator>>(std::istream& in,
            ParametersInterface& obj) {
            std::string program, ip, port, filename, request;
            in >> program >> ip >> port >> filename;
            SocketRequestTypeList requests;
            while (in.good()) {
                in >> request;
                if (in.good()) requests.push_back(request);
            }
            obj.setProgram(program);
            obj.setIP(ip);
            obj.setPort(stoi(port));
            obj.setFilename(filename);
            obj.setRequests(requests);
            return in;
        }
        /**
         * @brief abstract class SocketPool
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */
        Parameters SocketPool::parameters(int argc, char const* argv[]) {
            if (argc < 4) {
                std::cout << "params: filename ip port" << std::endl;
                throw RSIException("params: filename ip port", __INFO__);
            }
            Parameters copy;
            std::stringstream ss;
            for (int i = 0; i < argc; i++) {
                ss << argv[i] << ' ';
                copy.push_back(argv[i]);
            }
            ss >> *this;
            return copy;
        }

    }  // namespace rsi
}  // namespace extras
