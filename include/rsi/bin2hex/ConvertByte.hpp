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

        using Byte = byte;
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
            // Hex(Byte byteValue) {
            //     int decimalValue = byteValue;
            //     std::stringstream ss;
            //     ss << std::hex << decimalValue;
            // }
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


