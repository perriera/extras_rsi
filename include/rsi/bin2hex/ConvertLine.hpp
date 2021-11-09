#ifndef _EXPARX_RSICONVERTLINE_HPP
#define _EXPARX_RSICONVERTLINE_HPP

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


        using HexLine = std::string;
        struct BinLine {
            BinLine() {
                for (int i = 0; i < SIZE; i++)
                    buffer[i] = 0;
            }
            static constexpr int const& SIZE = 42;
            byte buffer[SIZE];
            bool operator==(const BinLine& rhs) const {
                for (int i = 0; i < SIZE; i++)
                    if (buffer[i] != rhs.buffer[i])
                        return false;
                return true;
            }

            bool operator!=(const BinLine& rhs) const {
                return !(*this == rhs);
            }
        };

        /**
         * @brief ConvertLineInterface
         *
         */
        interface ConvertLineInterface {
            virtual BinLine hexToBin(const HexLine& hexLine) const pure;
            virtual HexLine binToHex(const BinLine& binLine) const pure;
        };


    }
}

#endif // _EXPARX_RSICONVERTLINE_HPP


