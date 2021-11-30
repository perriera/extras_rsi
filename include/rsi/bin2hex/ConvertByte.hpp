/**
 * @file ConvertByte.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef _EXPARX_RSICONVERTBYTE_HPP
#define _EXPARX_RSICONVERTBYTE_HPP

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
#include <vector>

namespace extras {
    namespace rsi {

        /**
         * @brief ByteArray, HexArray
         *
         */
        using ByteArray = std::vector<byte>;
        using HexArray = std::string;

        /**
         * @brief hexToBytes
         * @param hex
         * @return std::vector<byte>
         */
        ByteArray hexToBytes(const HexArray& hex);

        /**
         * @brief bytesToHex
         *
         * @param data
         * @param len
         * @return std::string
         */
        HexArray bytesToHex(byte* data, int len);
        HexArray bytesToHex(ByteArray data);


    }
}

#endif // _EXPARX_RSICONVERTBYTE_HPP


