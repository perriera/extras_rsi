#ifndef _EXPARX_RSICONVERTFILE_HPP
#define _EXPARX_RSICONVERTFILE_HPP

/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

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
            virtual HexFile convertToHex(std::istream& inBin, std::ostream& outHex) const pure;
            virtual BinFile convertToBin(std::istream& inBin, std::ostream& outHex) const pure;
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
            virtual HexFile convertToHex(std::istream& inBin, std::ostream& outHex) const override;
            virtual BinFile convertToBin(std::istream& inHex, std::ostream& outBin) const override;
        };
    }
}

#endif // _EXPARX_RSICONVERTFILE_HPP


