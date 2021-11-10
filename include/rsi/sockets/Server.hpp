#ifndef _EXPARX_RSISOCKETSSERVER_HPP
#define _EXPARX_RSISOCKETSSERVER_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/sockets/PortAuthority.hpp>
#include <rsi/sockets/Pool.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

/**
 * @brief
 *
 */

namespace extras {
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

        concrete class SocketPoolServer extends SocketPool with
            SocketPoolServerInterface {
            struct sockaddr_in _server_addr;
            struct sockaddr_in _new_addr;
            int _server_socket;
            int _client_socket;
            PortAuthority _PortAuthority;

        public:
            virtual PortAuthority& portAuthority() override { return _PortAuthority; }
            virtual void connect() override;
            virtual void accept() override;
            virtual void close() const override;
            virtual void transfer() const override;

        };

    }
}

#endif // _EXPARX_RSISOCKETSSERVER_HPP

