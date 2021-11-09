#ifndef _EXPARX_RSICONVERTFILE_HPP
#define _EXPARX_RSICONVERTFILE_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <extras/interfaces.hpp>
#include <rsi/bin2hex/ConvertLine.hpp>
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

        using HexFile = std::vector<HexLine>;
        using BinFile = std::vector<BinLine>;

        /**
         * @brief ConvertFileInterface
         *
         */
        interface ConvertFileInterface {
            virtual BinFile hexToBin(const HexFile& hexFile) const pure;
            virtual HexFile binToHex(const BinFile& binFile) const pure;
        };

    }
}

#endif // _EXPARX_RSICONVERTFILE_HPP


