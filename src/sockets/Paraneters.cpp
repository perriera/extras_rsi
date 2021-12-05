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

        /**
         * @brief ParametersInterface ostream
         *
         * @param out
         * @param obj
         * @return std::ostream&
         */

        std::ostream& operator<<(std::ostream& out,
            const SocketParaneters& obj) {
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
            SocketParaneters& obj) {
            in >> obj._program >> obj._ip >> obj._port >> obj._filename;
            obj._requests.clear();
            while (in.good()) {
                SocketRequestType request;
                in >> request;
                if (in.good())  obj._requests.push_back(request);
            }
            return in;
        }


        /**
         * @brief abstract class SocketPool
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */
        Parameters SocketParaneters::parameters(int argc, char const* argv[]) {
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
