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
#include <extras_rsi/prototype/requests/RequestTypeThree.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief RequestTypeCompilerTypeThree::compile()
         *
         * @param client
         * @param portAuthority
         * @return RequestTypeCompilation
         */
        RequestTypeCompilation RequestTypeCompilerTypeThree::compile(
            const sockets::ParametersInterface& client,
            PortAuthorityInterface& portAuthority) const {

            std::vector<std::string> keywords;
            std::map<int, std::vector<std::string> >script;

            for (rsi::RequestType request : client.requests()) {
                auto entry = script[script.size() - 1];
                if (isParameter(request)) {
                    if (entry.size() == 0)
                        throw "No entry";
                    script[script.size() - 1].push_back(request);
                }
                else {
                    rsi::ParameterList list;
                    list.push_back(request);
                    keywords.push_back(request);
                    script[script.size()] = list;
                }
            }

            script.erase(-1);

            rsi::RequestTypeList list;
            int lineNo = 0;
            for (auto entry : script) {
                auto port = portAuthority.request();
                std::stringstream ss;
                ss << keywords[lineNo] << ' ';
                ss << client.ip() << ' ';
                ss << port << ' ';
                ss << client.filename();
                std::string line = ss.str();
                list.push_back(line);
                entry.second.erase(entry.second.begin());
                for (auto parm : entry.second) {
                    std::stringstream ss;
                    auto port = portAuthority.request();
                    ss << keywords[lineNo] << ' ';
                    ss << client.ip() << ' ';
                    ss << port << ' ';
                    ss << parm << ' ';
                    std::string line = ss.str();
                    list.push_back(line);
                }
                lineNo++;
            }

            return rsi::RequestTypeCompilation(list, _socket);
        }

    }  // namespace rsi
}  // namespace extras
