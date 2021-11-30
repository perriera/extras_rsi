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

#ifndef _EXPARX_RSICONVERTLINE_HPP
#define _EXPARX_RSICONVERTLINE_HPP

#include <extras/interfaces.hpp>
#include <rsi/bin2hex/ConvertByte.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief ConvertLineInterface
         *
         */

        using HexLine = HexArray;
        using BinLine = ByteArray;

        interface ConvertLineInterface {
            virtual BinLine hexToBin(const HexLine& hexLine) const pure;
            virtual HexLine binToHex(const BinLine& binLine) const pure;
        };

        concrete class ConvertLine implements ConvertLineInterface {
        public:
            virtual BinLine hexToBin(const HexLine& hexLine) const override {
                return rsi::hexToBytes(hexLine);
            }
            virtual HexLine binToHex(const BinLine& binLine) const override {
                return rsi::bytesToHex(binLine);
            }
        };

    }
}

#endif // _EXPARX_RSICONVERTLINE_HPP


