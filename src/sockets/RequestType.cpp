#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <rsi/sockets/Types.hpp>
#include <rsi/sockets/Client.hpp>
#include <rsi/sockets/RequestType.hpp>
#include <rsi/sockets/PortAuthority.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// virtual const Parameter &program() const pure;
// virtual const Parameter &ip() const pure;
// virtual const Parameter &port() const pure;
// virtual const Parameter &filename() const pure;
// virtual const SocketRequestTypeList &requests() const pure;

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
            const SocketPoolParametersInterface& client,
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
