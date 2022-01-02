/**
 * @file ParametersInterface.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief ParametersInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSI_PARAMETERS_HPP
#define _EXPARX_RSI_PARAMETERS_HPP

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
#include <extras_rsi/remote/ServiceInterface.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief ParametersInterface
         *
         */
        interface ParametersInterface {

            virtual void parse(int argc, char const* argv[]) pure;
            virtual Parameter parameters() const pure;
            virtual const Parameter& address() const pure;
            virtual const Parameter& port() const pure;
            virtual const Filenames& filenames() const pure;
            virtual ParameterList list() const pure;

        };

        /**
         * @brief Invocation class
         *
         */
        concrete class ParametersX implements ParametersInterface {

            friend std::ostream& operator<<(std::ostream& out, const ParametersX& obj);
            friend std::istream& operator>>(std::istream& in, ParametersX& obj);

            Parameter _address;
            Parameter _port;
            Filenames _filenames;

        public:

            /**
             * @brief Construct a new Invocation object
             *
             * @param portAuthority
             */
            ParametersX() {};

            ParametersX(const Parameter& param) {
                std::stringstream ss;
                ss << param;
                ss >> *this;
            };

            ParametersX(int argc, char const* argv[]) {
                parse(argc, argv);
            }

            /**
             * @brief InvocationInterface implementation
             *
             */
            virtual void parse(int argc, char const* argv[]) override;
            virtual Parameter parameters() const override;
            virtual  const Parameter& address() const override { return _address; }
            virtual  const Parameter& port() const override { return _port; }
            virtual  const Filenames& filenames() const override { return _filenames; }
            virtual  ParameterList list() const override {
                ParameterList list;
                Parameter param = address() + ":" + port();
                list.push_back(param);
                for (auto filename : filenames()) {
                    list.push_back(filename);
                }
                return list;
            }

        };


    }
}

#endif // _EXPARX_RSI_PARAMETERS_HPP


