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

        struct Hex {
            friend std::ostream& operator<<(std::ostream& out,
                const Hex& obj) {
                out << obj._hex;
                return out;
            }
            friend std::istream& operator>>(std::istream& in,
                Hex& obj) {
                in >> obj._hex;
                return in;
            }

            std::string _hex = "00";
            Hex() { }
            Hex(int decimalValue) {
                std::stringstream ss;
                ss << std::hex << decimalValue;
            }
            bool operator==(const Hex& rhs) const {
                return _hex == rhs._hex;
            }

            bool operator!=(const Hex& rhs) const {
                return !(*this == rhs);
            }
            operator const std::string& () const {
                return _hex;
            }
        };

        /**
         * @brief HexToBytes
         * @ref https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array
         * @param hex
         * @return std::vector<char>
         */
        std::vector<char> HexToBytes(const std::string& hex) {
            std::vector<char> bytes;

            for (unsigned int i = 0; i < hex.length(); i += 2) {
                std::string byteString = hex.substr(i, 2);
                char byte = (char)strtol(byteString.c_str(), NULL, 16);
                bytes.push_back(byte);
            }

            return bytes;
        }

        struct Byte {
            friend std::ostream& operator<<(std::ostream& out,
                const Byte& obj) {
                out << obj._byte;
                return out;
            }
            friend std::istream& operator>>(std::istream& in,
                Byte& obj) {
                in >> obj._byte;
                return in;
            }
            byte _byte;
            Byte() { }
            Byte(int decimalValue) {
                _byte = (byte)decimalValue;
            }
            Byte(const Hex& hex) {
                auto binary = HexToBytes(hex);
                _byte = binary[0];
            }
            bool operator==(const Byte& rhs) const {
                return _byte == rhs._byte;
            }

            bool operator!=(const Byte& rhs) const {
                return !(*this == rhs);
            }
            operator const byte& () const {
                return _byte;
            }
        };



        /**
         * @brief ConvertLineInterface
         *
         */
        interface ConvertByteInterface {
            virtual Byte hexToByte(Hex cahr) const pure;
            virtual Hex byteToHex(Byte btye) const pure;
        };


    }
}

#endif // _EXPARX_RSICONVERTBYTE_HPP


