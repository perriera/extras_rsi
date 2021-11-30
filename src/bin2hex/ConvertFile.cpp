
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
 * The above copyright notice and  this permission  notice shall be
 * included in all copies or  substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESSED  OR   IMPLIED,  INCLUDING   BUT  NOT  LIMITED  TO  THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT.  IN  NO  EVENT  SHALL EXPARX  INCORPORATED
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER  IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM, OUT  OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR  OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Except  as  contained  in this  notice, the  name of  the EXPARX
 * INCORPORATED shall not  be used in  advertising or  otherwise to
 * promote the sale, use or other dealings in this Software without
 * prior written authorization from EXPARX INCORPORATED.
 *
 * exparx.com and www.exparx.com  are domain names  registered with
 * EXPARX INCORPORATED, (other GPL-themed licenses are included).
 *
 */

#include <iostream>
#include <rsi/bin2hex/ConvertFile.hpp>

using namespace std;

namespace extras {
    namespace rsi {

        rsi::BinFile ConvertFile::loadBin(std::istream& in, int columns) const {
            rsi::BinFile binFile;
            rsi::ConvertLine converter;
            while (in.good()) {
                rsi::BinLine line;
                for (int i = 0; i < columns && in.good();i++) {
                    byte b = 0;
                    in >> std::noskipws >> b;
                    if (in.good())
                        line.push_back(b);
                }
                binFile.push_back(line);
            }
            return binFile;
        }

        rsi::HexFile ConvertFile::loadHex(std::istream& in) const {
            rsi::HexFile hexFile;
            rsi::ConvertLine converter;
            while (in.good()) {
                rsi::HexLine line;
                getline(in, line);
                hexFile.push_back(line);
            }
            return hexFile;

        }

        void ConvertFile::saveBin(std::ostream& out, const BinFile& binFile) const {
            for (auto binLine : binFile) {
                for (auto b : binLine)
                    out << std::skipws << b;
            }
        }

        void ConvertFile::saveHex(std::ostream& out, const HexFile& hexFile) const {
            for (auto hexLine : hexFile) {
                out << hexLine << std::endl;
            }
        }

        HexFile ConvertFile::convertToHex(std::istream& inBin, std::ostream& outHex) const {
            rsi::BinFile binFile = loadBin(inBin, 40);
            rsi::HexFile hexFile = binToHex(binFile);
            saveHex(outHex, hexFile);
            return hexFile;
        }

        BinFile ConvertFile::convertToBin(std::istream& inHex, std::ostream& outBin) const {
            rsi::HexFile hexFile = loadHex(inHex);
            rsi::BinFile binFile = hexToBin(hexFile);
            saveBin(outBin, binFile);
            return binFile;
        }

    }
}
