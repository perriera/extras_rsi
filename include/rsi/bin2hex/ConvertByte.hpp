#ifndef _EXPARX_RSICONVERTBYTE_HPP
#define _EXPARX_RSICONVERTBYTE_HPP

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

namespace extras {
    namespace rsi {

        /**
         * @brief SocketPoolInterface types
         *
         */

        using Byte = byte;
        using Char = char;

        /**
         * @brief ConvertLineInterface
         *
         */
        interface ConvertByteInterface {
            virtual Byte charToByte(Char cahr) const pure;
            virtual Char byteToChar(Byte btye) const pure;
        };


    }
}

#endif // _EXPARX_RSICONVERTBYTE_HPP


