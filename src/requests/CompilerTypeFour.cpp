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
#include <extras_rsi/prototype/requests/RequestTypeFour.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief RequestTypeCompilerTypeFour::compile()
         *
         * @param client
         * @param portAuthority
         * @return RequestTypeCompilation
         */
        RequestTypeCompilation RequestTypeCompilerTypeFour::compile(
            const sockets::ParametersInterface& client,
            PortAuthorityInterface& portAuthority) const {

            std::vector<std::string> extra_files = client.requests();

            rsi::RequestTypeList list;
            {
                std::stringstream ss;
                ss << "upload" << ' ';
                ss << client.ip() << ' ';
                ss << portAuthority.request() << ' ';
                ss << client.filename();
                std::string line = ss.str();
                list.push_back(line);
            }
            for (auto entry : extra_files) {
                std::stringstream ss;
                ss << "upload" << ' ';
                ss << client.ip() << ' ';
                ss << portAuthority.request() << ' ';
                ss << entry;
                std::string line = ss.str();
                list.push_back(line);
            }
            {
                std::stringstream ss;
                ss << "vendor" << ' ';
                ss << client.ip() << ' ';
                ss << portAuthority.request() << ' ';
                ss << client.filename() << ' ';
                for (auto entry : extra_files)
                    ss << entry << ' ';
                std::string line = ss.str();
                list.push_back(line);
            }
            {
                std::stringstream ss;
                ss << "download" << ' ';
                ss << client.ip() << ' ';
                ss << portAuthority.request() << ' ';
                ss << client.filename();
                std::string line = ss.str();
                list.push_back(line);
            }

            return rsi::RequestTypeCompilation(list, _socket);

        }

    }  // namespace rsi
}  // namespace extras
