
#include <iostream>
#include <rsi/bin2hex/ConvertLine.hpp>

namespace extras {
    namespace rsi {

        /**
         * @brief hexToBytes
         * @ref https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array
         * @param hex
         * @return std::vector<byte>
         */
        std::vector<byte> hexToBytes(const std::string& hex) {
            std::vector<byte> bytes;
            for (unsigned int i = 0; i < hex.length(); i += 2) {
                std::string byteString = hex.substr(i, 2);
                char byte = (char)strtol(byteString.c_str(), NULL, 16);
                bytes.push_back(byte);
            }
            return bytes;
        }

        /**
         * @brief bytesToHex
         * @ref https://codereview.stackexchange.com/questions/78535/converting-array-of-bytes-to-the-hex-string-representation
         * @param data
         * @param len
         * @return std::string
         */

        constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                   '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

        std::string bytesToHex(byte* data, int len)
        {
            std::string s(len * 2, ' ');
            for (int i = 0; i < len; ++i) {
                s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
                s[2 * i + 1] = hexmap[data[i] & 0x0F];
            }
            return s;
        }

        std::string bytesToHex(std::vector<byte> data)
        {
            std::string s(data.size() * 2, ' ');
            for (long unsigned int i = 0; i < data.size(); ++i) {
                s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
                s[2 * i + 1] = hexmap[data[i] & 0x0F];
            }
            return s;
        }

    }
}
