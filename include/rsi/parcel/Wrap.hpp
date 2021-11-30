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

#ifndef _EXPARX_WRAP_HPP
#define _EXPARX_WRAP_HPP

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/exceptions.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <ng_imploder/imploder/Imploder.hpp>

namespace extras {
    namespace rsi {
        /**
         * @brief WrapInterface
         *
         */

        interface WrapInterface {

            virtual Filename wrap(const Filename& filename) const pure;
            virtual Filename unWrap(const Filename& filename) const pure;
            virtual Filename merge(const Filename& filename) const pure;
            virtual Filename clean(const Filename& filename) const pure;
            virtual Filename wrapped(const Filename& filename) const pure;
            virtual Filename unWrapped(const Filename& filename) const pure;

            bool operator==(const WrapInterface& rhs) const;
            bool operator!=(const WrapInterface& rhs) const {
                return !(*this == rhs);
            }
        };

        /**
         * @brief ParcelImploder
         *
         */
        concrete class ParcelImploder implements WrapInterface {

        public:
            virtual Filename wrap(const Filename& filename) const override;
            virtual Filename unWrap(const Filename& filename) const override;
            virtual Filename merge(const Filename& filename) const override;
            virtual Filename clean(const Filename& filename) const override;
            virtual Filename wrapped(const Filename& filename) const override;
            virtual Filename unWrapped(const Filename& filename) const override;

        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_WRAP_HPP
