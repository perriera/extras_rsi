/**
 * @file version.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief Project Version Number
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _RSI_VERSION_HPP
#define _RSI_VERSION_HPP

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

  /**
   * @file version.hpp
   * @author Matt Williams (matt@perriera.com)
   * @author Perry Anderson (perry@perriera.com)
   * @brief Adds version support for Cmake script
   * @date 2021-08-08
   */

#define RSI_VER_MAJOR 3
#define RSI_VER_MINOR 3
#define RSI_VER_PATCH 0

#define RSI_VERSION \
  (RSI_VER_MAJOR * 10000 + RSI_VER_MINOR * 100 + RSI_VER_PATCH)

#endif// _RSI_VERSION_HPP
