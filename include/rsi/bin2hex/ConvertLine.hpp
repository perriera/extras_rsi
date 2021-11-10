#ifndef _EXPARX_RSICONVERTLINE_HPP
#define _EXPARX_RSICONVERTLINE_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <extras/interfaces.hpp>
#include <rsi/bin2hex/ConvertByte.hpp>
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
         * @brief ConvertLineInterface
         *
         */

        using HexLine = std::string;
        using BinLine = std::vector<byte>;

        interface ConvertLineInterface {
            virtual BinLine hexToBin(const HexLine& hexLine) const pure;
            virtual HexLine binToHex(const BinLine& binLine) const pure;
        };

        concrete class ConvertLine implements ConvertLineInterface {
        public:
            virtual BinLine hexToBin(const HexLine& hexLine) const override {
                return rsi::hexToBytes(hexLine);
            }
            virtual HexLine binToHex(const BinLine& binLine) const override {
                return rsi::bytesToHex(binLine);
            }
        };

    }
}

#endif // _EXPARX_RSICONVERTLINE_HPP


