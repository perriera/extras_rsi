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

#include <rsi/parcel/Parcel.hpp>
#include <rsi/exceptions.hpp>
#include <rsi/parcel/Wrap.hpp>
#include <ng_imploder/imploder/Imploder.hpp>
#include <rsi/exceptions.hpp>
#include <extras/filesystem/system.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace rsi {

        /**
         * @brief wrap()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::wrap(const Filename& filename) const {
            ng::Imploder imploder(filename);
            imploder.implode();
            rsi::Parcel parcel(imploder.imploded());
            parcel.pack();
            return parcel.packed();
        }

        Filename ParcelImploder::wrapped(const Filename& filename) const {
            ng::Imploder imploder(filename);
            rsi::Parcel parcel(imploder.imploded());
            return parcel.packed();
        }

        /**
         * @brief unWrap()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::unWrap(const Filename& filename) const {
            ng::Imploder imploder(filename);
            rsi::Parcel parcel(imploder.imploded());
            parcel.unpack();
            parcel.merge();
            parcel.clean();
            if (fs::exists(imploder.original())) {
                imploder.explode();
                return imploder.exploded();
            }
            return parcel.original();
        }

        Filename ParcelImploder::unWrapped(const Filename& filename) const {
            ng::Imploder imploder(filename);
            rsi::Parcel parcel(imploder.imploded());
            return imploder.exploded();
        }

        /**
         * @brief merge()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::merge(const Filename& filename) const {
            ng::Imploder imploder(filename);
            if (fs::exists(imploder.original())) {
                imploder.merge();
                return filename;
            }
            rsi::FileNotFoundException::assertion(imploder.imploded(), __INFO__);
            auto a = imploder.imploded();
            auto b = imploder.original();
            auto cmd = "mv " + a + " " + b;
            SystemException::assertion(cmd, __INFO__);
            imploder.clean();
            return filename;
        }

        /**
         * @brief clean()
         *
         * @param filename
         * @return Filename
         */
        Filename ParcelImploder::clean(const Filename& filename) const {
            ng::Imploder imploder(filename);
            rsi::Parcel parcel(imploder.imploded());
            parcel.clean();
            imploder.clean();
            return filename;
        }


    }
}
