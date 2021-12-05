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
 * (See LICENSE.md for complete details)
 *
 */

#include <arpa/inet.h>
#include <unistd.h>

#include <extras_rsi/sockets/Client.hpp>
#include <extras_rsi/sockets/RequestType.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
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
            const sockets::ParametersInterface& client,
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
