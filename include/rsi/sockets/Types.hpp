#ifndef _EXPARX_RSISOCKETSTYPES_HPP
#define _EXPARX_RSISOCKETSTYPES_HPP

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


