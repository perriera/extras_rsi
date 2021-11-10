#ifndef _EXPARX_RSICONVERTFILE_HPP
#define _EXPARX_RSICONVERTFILE_HPP

#include <extras/interfaces.hpp>
#include <rsi/bin2hex/ConvertLine.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief ConvertFileInterface
         *
         */

        using HexFile = std::vector<HexLine>;
        using BinFile = std::vector<BinLine>;

        interface ConvertFileInterface {
            virtual BinFile hexToBin(const HexFile& hexFile) const pure;
            virtual HexFile binToHex(const BinFile& binFile) const pure;
            virtual BinFile loadBin(std::istream& in, int columns) const pure;
            virtual HexFile loadHex(std::istream& in) const pure;
            virtual void saveBin(std::ostream& in, const BinFile& binFile) const pure;
            virtual void saveHex(std::ostream& in, const HexFile& hexFile) const pure;
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
            virtual BinFile loadBin(std::istream& in, int columns = 40) const override;
            virtual HexFile loadHex(std::istream& in) const override;
            virtual void saveBin(std::ostream& in, const BinFile& binFile) const override;
            virtual void saveHex(std::ostream& in, const HexFile& hexFile) const override;
        };
    }
}

#endif // _EXPARX_RSICONVERTFILE_HPP


