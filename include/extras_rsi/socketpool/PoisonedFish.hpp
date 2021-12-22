/**
 * @file PoisonedFish.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief PoisonedFishInterface
 * @version 0.1
 * @date 2021-12-22
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_POISONEDFISH_HPP
#define _EXPARX_POISONEDFISH_HPP

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
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief PoisonedFishInterface
         *
         * Starting a server, (on a socket port) is one thing, getting it
         * it to stop, (in an orderly fashion) is another. We use what is
         * known as the Poisoned Fish Design Pattern. Such that if a special
         * code is sent to the server it will shutdown operations.
         *
         */

        using PoisonedFishKey = std::string;

        interface PoisonedFishInterface {
            virtual bool poisonedFishReceived(
                const PoisonedFishKey& msg) const pure;
            virtual void killServers() const pure;
        };

    }
}

#endif // _EXPARX_POISONEDFISH_HPP


