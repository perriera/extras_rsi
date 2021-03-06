/**
 * @file PortAuthority.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief PortAuthorityInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISOCKETSPORTAUTHORITY_HPP
#define _EXPARX_RSISOCKETSPORTAUTHORITY_HPP

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
#include <extras_rsi/remote/sockets/Types.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief PortAuthorityInterface
         *
         */

        interface PortAuthorityInterface {
            /**
             * @brief serversocketport
             * @return of the primary port providing the ports
             *
             */
            virtual const PortNumber& serversocketport() const pure;

            /**
             * @brief request of the website providing the ports
             * @return a port number that can be used by connect()/accept()
             *
             * The general idea is that the port # being returned will not
             * be needed again for a while. The idea is that whatever process
             * needs that unique port # will dispense with it quickly.
             *
             * The server portion would create a seversocket with accept()
             * expecting a connect to appear, (within 7 seconds, perhaps)
             * to carry out whatever is required.
             *
             * @note It would be good to ensure that the server can timeout.
             * (aka. otherwise you can expect a port collision)
             *
             */
            virtual PortNumber request() pure;
        };

        /**
         * @brief PortAuthority
         *
         */

        concrete class PortAuthority implements PortAuthorityInterface {
            PortServerNumber _port;
            PortServerNumber _start;
            PortServerNumber _size;
            PortServerNumber _next;

        public:
            static auto instance() -> PortAuthorityInterface& {
                static PortAuthority compiler;
                return compiler;
            }

            PortAuthority(PortNumber port = 8080, PortRangeStart start = 9000,
                PortRangeSize size = 1000)
                : _port(port), _start(start), _size(size), _next(0) {};

            virtual const PortNumber& serversocketport() const override {
                return _port;
            };

            PortNumber request() override {
                auto result = _next++;
                _next = _next % _size;
                return _start + result;
            }
        };




    }
}

#endif // _EXPARX_RSISOCKETSPORTAUTHORITY_HPP


