#ifndef _RSI_VERSION_HPP
#define _RSI_VERSION_HPP

/**
 * @file version.hpp
 * @author Matt Williams (matt@perriera.com)
 * @author Perry Anderson (perry@perriera.com)
 * @brief Adds version support for Cmake script
 * @date 2021-08-08
 */

#define RSI_VER_MAJOR 1
#define RSI_VER_MINOR 1
#define RSI_VER_PATCH 4

#define RSI_VERSION \
  (RSI_VER_MAJOR * 10000 + RSI_VER_MINOR * 100 + RSI_VER_PATCH)

#endif// _RSI_VERSION_HPP
