/**
 * @file Types.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief Various types used by package
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISOCKETSTYPES_HPP
#define _EXPARX_RSISOCKETSTYPES_HPP

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

#include <extras/interfaces.hpp>
#include <iostream>
#include <sstream>
#include <map>
#include <deque>
#include <vector>

namespace extras {
    namespace rsi {

        /**
         * @brief SocketPoolInterface types
         *
         */

        using Parameter = std::string;
        using Parameters = std::deque<Parameter>;
        using ParameterList = std::vector<Parameter>;

        using PortDomainName = std::string;
        using PortNumber = int;
        using PortServerNumber = int;
        using PortRangeStart = int;
        using PortRangeSize = int;

        using Filename = std::string;
        using IP = std::string;
        using Port = int;
        using Async = bool;

        using PortNumber = int;
        using Socket = int;
        using PortNumberPool = std::vector<PortNumber>;
        using SocketRequestType = std::string;
        using SocketRequestTypeList = std::vector<SocketRequestType>;
        using SocketRequestTypeMap = std::map<PortNumber, SocketRequestType>;

        using RequestType = std::string;
        using RequestTypeList = std::vector<RequestType>;


    }
}

#endif // _EXPARX_RSISOCKETSTYPES_HPP


