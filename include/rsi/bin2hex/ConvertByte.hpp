#ifndef _EXPARX_RSICONVERTBYTE_HPP
#define _EXPARX_RSICONVERTBYTE_HPP

#include <extras/interfaces.hpp>
#include <iostream>
#include <vector>

namespace extras {
    namespace rsi {

        /**
         * @brief hexToBytes
         * @param hex
         * @return std::vector<byte>
         */
        std::vector<byte> hexToBytes(const std::string& hex);

        /**
         * @brief bytesToHex
         *
         * @param data
         * @param len
         * @return std::string
         */
        std::string bytesToHex(byte* data, int len);
        std::string bytesToHex(std::vector<byte> data);


    }
}

#endif // _EXPARX_RSICONVERTBYTE_HPP


