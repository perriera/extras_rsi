/**
 * @file Parameters.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief ParametersInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISOCKETSPARAMETERS_HPP
#define _EXPARX_RSISOCKETSPARAMETERS_HPP

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
#include <extras_rsi/sockets/Types.hpp>
#include <iostream>

namespace extras {
    namespace rsi {
        namespace sockets {

            /**
             * @brief ParametersInterface
             *
             */

            interface ParametersInterface {
                virtual Parameters parameters(int argc, char const* argv[]) pure;
                virtual  Parameter program() const pure;
                virtual  Parameter ip() const pure;
                virtual  Parameter port() const pure;
                virtual  Parameter filename() const pure;
                virtual  SocketRequestTypeList requests() const pure;
            };

        }

        /**
         * @brief class SocketParaneters
         *
         */
        concrete class SocketParaneters implements sockets::ParametersInterface {
            friend std::ostream& operator<<(std::ostream& out,
                const SocketParaneters& obj);
            friend std::istream& operator>>(std::istream& in,
                SocketParaneters& obj);

            Parameters _parameters;
            Parameter _program;
            Parameter _ip;
            Parameter _port;
            Parameter _filename;
            SocketRequestTypeList _requests;

        public:

            virtual Parameters parameters(int argc, char const* argv[]) override;
            virtual  Parameter program() const override { return _program; };
            virtual  Parameter ip() const override { return _ip; };
            virtual  Parameter port() const override { return _port; };
            virtual  Parameter filename() const override { return _filename; };
            virtual  SocketRequestTypeList requests() const override { return _requests; };

            bool operator==(const SocketParaneters& rhs) const {
                std::stringstream ssA;
                ssA << *this;
                std::string testA = ssA.str();
                std::stringstream ssB;
                ssB << rhs;
                std::string testB = ssB.str();
                return testB == testA;
            }

            bool operator!=(const SocketParaneters& rhs) const {
                return !(*this == rhs);
            }

        };
    }
}

#endif // _EXPARX_RSISOCKETSPARAMETERS_HPP


