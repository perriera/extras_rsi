/**
 * @file RequestType.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief RequestTypeCompilationInterface, RequestTypeCompilerInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSIREQUESTTYPE_HPP
#define _EXPARX_RSIREQUESTTYPE_HPP

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
#include <extras_rsi/sockets/PortAuthority.hpp>
#include <extras_rsi/sockets/LineBlock.hpp>
#include <iostream>

  /**
   * @brief
   *
   */

namespace extras {
    namespace rsi {

        /**
         * @brief RequestTypeInterface
         *
         * All the types of services that can be run on a remote server.
         *
         */

        interface RequestTypeCompilationInterface {
            virtual void setCompilation(const RequestTypeList& list) pure;
            virtual RequestTypeList compilation() const pure;
        };

        /**
         * @brief RequestTypeCompilation
         *
         */
        concrete class RequestTypeCompilation implements
            RequestTypeCompilationInterface with LineBlockInterface {
            friend std::ostream& operator<<(std::ostream& out, const RequestTypeCompilation& obj);
            friend std::istream& operator>>(std::istream& in, RequestTypeCompilation& obj);

            RequestTypeList _requestTypeList;
            int _socket = -1;

        public:
            RequestTypeCompilation(const RequestTypeList requestTypeList, int socket)
                : _requestTypeList(requestTypeList), _socket(socket) {}

            RequestTypeCompilation(const std::string& rawString, int socket) : _socket(socket) {
                std::stringstream ss;
                ss << rawString;
            }
            RequestTypeCompilation(int socket) : _socket(socket) {}

            virtual void setCompilation(const RequestTypeList& list) override {
                _requestTypeList = list;
            };

            virtual RequestTypeList compilation() const override {
                return _requestTypeList;
            };

            virtual void send_line_block(const LinePacket& msg) const override;
            virtual LinePacket read_line_block() override;

            operator std::string() {
                std::stringstream ss;
                ss << *this;
                return ss.str();
            }

            bool operator==(const RequestTypeCompilation& rhs) const {
                return compilation() == rhs.compilation();
            }

            bool operator!=(const RequestTypeCompilation& rhs) const {
                return !(*this == rhs);
            }
        };

        /**
         * @brief RequestTypeCompilerInterface
         *
         */

        interface RequestTypeCompilerInterface {
            virtual RequestTypeCompilation compile(
                const sockets::ParametersInterface& client,
                PortAuthorityInterface& portAuthority) const pure;
        };

        /**
         * @brief RequestTypeCompilerTypeOne
         *
         */
        concrete class RequestTypeCompilerTypeOne implements RequestTypeCompilerInterface {
            int _socket = -1;
        public:
            RequestTypeCompilerTypeOne(int socket) : _socket(socket) {}
            virtual RequestTypeCompilation compile(
                const sockets::ParametersInterface& client,
                PortAuthorityInterface& portAuthority) const override;
            virtual RequestTypeCompilation compile(
                const sockets::ParametersInterface& client) const {
                return compile(client, PortAuthority::instance());
            }
        };


    }
}

#endif // _EXPARX_RSIREQUESTTYPE_HPP


