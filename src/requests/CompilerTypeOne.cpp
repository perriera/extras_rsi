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

#include <extras_rsi/socketpool/Client.hpp>
#include <extras_rsi/prototype/requests/RequestTypeOne.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief RequestTypeCompilerTypeOne::compile()
         *
         * @param client
         * @param portAuthority
         * @return RequestTypeCompilation
         */
        RequestTypeCompilation RequestTypeCompilerTypeOne::compile(
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
            return rsi::RequestTypeCompilation(list, _socket);
        }

    }  // namespace rsi
}  // namespace extras
