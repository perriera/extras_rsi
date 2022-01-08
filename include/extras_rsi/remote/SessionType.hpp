/**
 * @file SessionType.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief SessionTypeCompilerInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISESSIONTYPE_HPP
#define _EXPARX_RSISESSIONTYPE_HPP

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
#include <extras_rsi/exceptions.hpp>
#include <extras_rsi/sockets/PortAuthority.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief SessionInterface
         *
         */

        using SessionType = std::string;
        using SessionTypeList = std::vector<SessionType>;

        interface SessionInterface {
            virtual void create()  pure;
            virtual extras::Directory session() const pure;
            virtual void destroy() const pure;
            virtual bool exists() const pure;
            virtual bool active() const pure;
            virtual extras::Pathname entry_name(const extras::Pathname& entry) const pure;
            virtual void add(const extras::Pathname& entry) const pure;
            virtual void remove(const extras::Pathname& entry) const pure;
            virtual SessionType sessionType(const rsi::RequestType& requestType) const pure;
            virtual SessionTypeList sessionTypeList(const rsi::RequestTypeList& requestType) const pure;
        };

        /**
         * @brief class Session
         *
         */
        concrete class Session implements SessionInterface {
            extras::Directory _directory;
        public:
            virtual void create()  override;
            virtual extras::Directory session() const override {
                return _directory;
            }
            virtual void destroy() const override;
            virtual bool exists() const override;
            virtual bool active() const override;
            virtual extras::Pathname entry_name(const extras::Pathname& entry) const override;
            virtual void add(const extras::Pathname& entry) const override;
            virtual void remove(const extras::Pathname& entry) const override;
            virtual SessionType sessionType(const rsi::RequestType& requestType) const override;
            virtual SessionTypeList sessionTypeList(const rsi::RequestTypeList& requestType) const override;
        };


    }
}

#endif // _EXPARX_RSISESSIONTYPE_HPP


