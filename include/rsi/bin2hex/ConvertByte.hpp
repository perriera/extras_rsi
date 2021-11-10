#ifndef _EXPARX_RSICONVERTBYTE_HPP
#define _EXPARX_RSICONVERTBYTE_HPP

#include <extras/interfaces.hpp>
#include <iostream>
#include <vector>

namespace extras {
    namespace rsi {

        /**
         * @brief HexToBytes
         * @ref https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array
         * @param hex
         * @return std::vector<char>
         */
        std::vector<byte> hexToBytes(const std::string& hex);

        /**
         * @brief https://codereview.stackexchange.com/questions/78535/converting-array-of-bytes-to-the-hex-string-representation
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


