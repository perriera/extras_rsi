/**
 * @file FileBlock.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief FileBlockInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSIFILEBLOCK_HPP
#define _EXPARX_RSIFILEBLOCK_HPP

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
         * @brief FileBlockInterface
         *
         */

        using FilePacket = std::string;

        interface FileBlockInterface {

            /**
             * @brief send_file_block
             *
             * Send a file of text and block until has been received.
             *
             * @param msg
             */
            virtual void send_file_block(const FilePacket& msg) const pure;

            /**
             * @brief write_file_block
             *
             * Block until a file of text has been received.
             *
             * @return FilePacket
             */
            virtual FilePacket write_file_block(const FilePacket& msg) const pure;
        };


    }
}

#endif // _EXPARX_RSIFILEBLOCK_HPP


