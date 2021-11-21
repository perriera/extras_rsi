#ifndef _EXPARX_PARCELIMPLODER_HPP
#define _EXPARX_PARCELIMPLODER_HPP

#include <extras/interfaces.hpp>
#include <rsi/parcel/Wrap.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <ng_imploder/imploder/Imploder.hpp>

namespace extras {
    namespace rsi {

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

        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_PARCELIMPLODER_HPP
