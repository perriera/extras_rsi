#ifndef _EXPARX_RSISOCKETSSERVER_HPP
#define _EXPARX_RSISOCKETSSERVER_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/sockets/PortAuthority.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

/**
 * @brief
 *
 */

namespace exparx {
    namespace rsi {

        /**
         * @brief SocketPoolClientInterface
         *
         * The idea is that we assign a port to be the authority on deligating
         * available port numbers, (from a range of port numbers). At the basic
         * level a series of predefined tokens are given to this interface. If all
         * tokens are reconized then a port number is returned for each token.
         *
         * The purpose of a token is to inform the SocketPool instance what type of
         * socket service will be expected to be running on that port. Earlier
         * prototypes to this just returned a single port number. However, it was
         * soon realized that perhaps more than one port is required and to inform
         * the socket pool manager in advance of what type of service to running on
         * that port would be advantageous.
         *
         * This version only returns a port number, a more enhanced version would
         * support IP addresses, (hence supporting socket pools over different IPs).
         *
         */

        interface SocketPoolServerInterface {
            virtual void connect() pure;
            virtual void accept() pure;
            virtual void close() const pure;
            virtual PortAuthority& portAuthority() pure;
        };


    }
}

#endif // _EXPARX_RSISOCKETSSERVER_HPP


