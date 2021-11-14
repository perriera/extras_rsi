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

        ServiceTypeList SocketPool::clients(
            const RequestTypeList& requests) const {
            rsi::ServiceTypeMap forClients;
            forClients["upload"] = "build/uploader_client";
            forClients["vendor"] = "build/vendor_client";
            forClients["download"] = "build/downloader_client";
            return common(forClients, requests);
        }

        ServiceTypeList SocketPool::servers(
            const RequestTypeList& requests) const {
            rsi::ServiceTypeMap forServers;
            forServers["upload"] = "build/uploader_server";
            forServers["vendor"] = "build/vendor_server";
            forServers["download"] = "build/downloader_server";
            return common(forServers, requests);
        }

    }  // namespace rsi
}  // namespace extras
