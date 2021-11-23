#ifndef _EXPARX_RSISOCKETSSEMAPHORE_HPP
#define _EXPARX_RSISOCKETSSEMAPHORE_HPP

#include <extras/interfaces.hpp>
#include <rsi/sockets/SocketPool.hpp>
#include <rsi/sockets/PortAuthority.hpp>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {

        /**
         * @brief SemaphoreInterface
         *
         */

        using Lock = std::string;

        interface SemaphoreInterface {
            virtual Lock lock(const Lock& lock) const pure;
            virtual Lock unlock(const Lock& lock) const pure;
        };


    }
}

#endif // _EXPARX_RSISOCKETSSEMAPHORE_HPP


