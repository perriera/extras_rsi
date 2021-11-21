#include <rsi/parcel/Parcel.hpp>
#include <rsi/exceptions.hpp>
#include <rsi/parcel/ParcelImploder.hpp>
#include <ng_imploder/imploder/Imploder.hpp>

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
            imploder.explode();
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
            imploder.merge();
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
