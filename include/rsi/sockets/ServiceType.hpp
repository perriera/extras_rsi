#ifndef _EXPARX_RSISERVICETYPE_HPP
#define _EXPARX_RSISERVICETYPE_HPP

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/sockets/PortAuthority.hpp>
#include <iostream>

/**
 * @brief
 *
 */

namespace extras {
    namespace rsi {

        /**
         * @brief ServiceTypeCompilerInterface
         *
         */

        using ServiceType = std::string;
        using ServiceTypeList = std::vector<ServiceType>;
        using ServiceTypeMap = std::map<ServiceType, ServiceType>;

        interface ServiceTypeCompilerInterface {
            virtual ServiceTypeList clients(
                const RequestTypeList& requests) const pure;
            virtual ServiceTypeList servers(
                const RequestTypeList& requests) const pure;
        };

    }
}

#endif // _EXPARX_RSISERVICETYPE_HPP


