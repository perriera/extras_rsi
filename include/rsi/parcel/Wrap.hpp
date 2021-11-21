#ifndef _EXPARX_WRAP_HPP
#define _EXPARX_WRAP_HPP

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/exceptions.hpp>

namespace extras {
    namespace rsi {
        /**
         * @brief PackedLineInterface
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */

        interface WrapInterface {

            virtual Filename wrap(const Filename& filename) const pure;
            virtual Filename unWrap(const Filename& filename) const pure;
            virtual Filename merge(const Filename& filename) const pure;
            virtual Filename clean(const Filename& filename) const pure;

            bool operator==(const WrapInterface& rhs) const;
            bool operator!=(const WrapInterface& rhs) const {
                return !(*this == rhs);
            }
        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_WRAP_HPP
