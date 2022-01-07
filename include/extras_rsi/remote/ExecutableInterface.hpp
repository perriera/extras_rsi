/**
 * @file ExecutableInterface.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief ExecutableInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSI_EXECUTABLE_HPP
#define _EXPARX_RSI_EXECUTABLE_HPP

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
#include <extras_rsi/remote/ServiceTypes.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief ExecutableInterface
         *
         */
        interface ExecutableInterface {

            /**
             * @brief internal()
             * @note run the service internally, (if possble)
             *
             * This is usually achieved either by running the class directly,
             * or through a thread, (using the C++11 style thread support)
             *
             * @param task
             */
            virtual void internal(const ServiceType& task) pure;

            /**
             * @brief external()
             * @note run the service externally, (if possble)
             *
             * This is usually achievd using the C/C++ standard library
             * system() called, (see extras::SystemException::assertion())
             *
             * @param task
             */
            virtual void external(const ServiceType& task) pure;

        };

    }
}

#endif // _EXPARX_RSI_EXECUTABLE_HPP


