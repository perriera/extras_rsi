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

#include <extras_rsi/sockets/Client.hpp>
#include <extras_rsi/requests/ServiceType.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {


        /**
         * @brief ServiceTypeCompilerVendor::common()
         *
         * @param map
         * @param requests
         * @return ServiceTypeList
         */
        ServiceTypeList ServiceTypeCompilerVendor::common(ServiceTypeMap& map,
            const RequestTypeList& requests) const {
            rsi::ServiceTypeList list;
            for (auto request : requests) {
                auto parts = extras::split(request, ' ');
                NoTokensException::assertion(parts.size(), __INFO__);
                auto serviceType = map[parts[0]];
                UnsupportedTokenException::assertion(serviceType, __INFO__);
                std::string line =
                    extras::replace_all(request, parts[0], serviceType);
                list.push_back(line);
            }
            return list;
        }

    }  // namespace rsi
}  // namespace extras
