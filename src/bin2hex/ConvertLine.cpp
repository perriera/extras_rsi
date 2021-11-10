
#include <iostream>

#include <rsi/bin2hex/ConvertLine.hpp>

using namespace std;

namespace extras {
    namespace rsi {

        std::vector<byte> hexToBytes(const std::string& hex) {
            std::vector<byte> bytes;

            for (unsigned int i = 0; i < hex.length(); i += 2) {
                std::string byteString = hex.substr(i, 2);
                char byte = (char)strtol(byteString.c_str(), NULL, 16);
                bytes.push_back(byte);
            }

            return bytes;
        }

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
