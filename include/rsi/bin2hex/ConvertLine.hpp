#ifndef _EXPARX_RSICONVERTLINE_HPP
#define _EXPARX_RSICONVERTLINE_HPP

#include <extras/interfaces.hpp>
#include <rsi/bin2hex/ConvertByte.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief ConvertLineInterface
         *
         */

        using HexLine = HexArray;
        using BinLine = ByteArray;

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


