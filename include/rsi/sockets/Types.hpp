#ifndef _EXPARX_RSISOCKETSTYPES_HPP
#define _EXPARX_RSISOCKETSTYPES_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <extras/interfaces.hpp>
#include <iostream>
#include <map>
#include <deque>
#include <sstream>
#include <vector>

/**
 * @brief
 *
 */

namespace exparx {
    namespace rsi {

        /**
         * @brief SocketPoolInterface
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

        using ServiceType = std::string;
        using ServiceTypeList = std::vector<ServiceType>;
        using ServiceTypeMap = std::map<ServiceType, ServiceType>;

    }
}

#endif // _EXPARX_RSISOCKETSTYPES_HPP


