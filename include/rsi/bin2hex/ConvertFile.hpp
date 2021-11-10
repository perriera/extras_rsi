#ifndef _EXPARX_RSICONVERTFILE_HPP
#define _EXPARX_RSICONVERTFILE_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <extras/interfaces.hpp>
#include <rsi/bin2hex/ConvertLine.hpp>
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

        using HexFile = std::vector<HexLine>;
        using BinFile = std::vector<BinLine>;

        /**
         * @brief ConvertFileInterface
         *
         */
        interface ConvertFileInterface {
            virtual BinFile hexToBin(const HexFile& hexFile) const pure;
            virtual HexFile binToHex(const BinFile& binFile) const pure;
        };

        concrete class ConvertFile implements ConvertFileInterface {
        public:
            virtual BinFile hexToBin(const HexFile& hexFile) const override {
                rsi::BinFile binFile;
                rsi::ConvertLine converter;
                for (auto hexLine : hexFile) {
                    rsi::BinLine binline = converter.hexToBin(hexLine);
                    binFile.push_back(binline);
                }
                return binFile;
            }
            virtual HexFile binToHex(const BinFile& binFile) const override {
                rsi::HexFile hexFile;
                rsi::ConvertLine converter;
                for (auto binLine : binFile) {
                    rsi::HexLine hexline = converter.binToHex(binLine);
                    hexFile.push_back(hexline);
                }
                return hexFile;
            }
        };
    }
}

#endif // _EXPARX_RSICONVERTFILE_HPP


