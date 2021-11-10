#ifndef _EXPARX_RSICONVERTBYTE_HPP
#define _EXPARX_RSICONVERTBYTE_HPP

#include <extras/interfaces.hpp>
#include <iostream>
#include <vector>

namespace extras {
    namespace rsi {

        /**
         * @brief ByteArray, HexArray
         *
         */
        using ByteArray = std::vector<byte>;
        using HexArray = std::string;

        /**
         * @brief hexToBytes
         * @param hex
         * @return std::vector<byte>
         */
        ByteArray hexToBytes(const HexArray& hex);

        /**
         * @brief bytesToHex
         *
         * @param data
         * @param len
         * @return std::string
         */
        HexArray bytesToHex(byte* data, int len);
        HexArray bytesToHex(ByteArray data);


    }
}

#endif // _EXPARX_RSICONVERTBYTE_HPP


