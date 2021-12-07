/**
 * @file Semaphores.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief SemaphoreInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISOCKETSSEMAPHORE_HPP
#define _EXPARX_RSISOCKETSSEMAPHORE_HPP

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
#include <extras_rsi/socketpool/SocketPool.hpp>
#include <extras_rsi/sockets/PortAuthority.hpp>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {

        /**
         * @brief SemaphoreInterface
         *
         */

        using Lock = std::string;

        interface SemaphoreInterface {
            virtual Lock lock(const Lock& lock)  pure;
            virtual Lock unlock(const Lock& lock)  pure;
        };


    }
}

#endif // _EXPARX_RSISOCKETSSEMAPHORE_HPP


