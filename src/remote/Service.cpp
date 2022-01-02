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

#include <arpa/inet.h>
#include <unistd.h>

#include <extras_rsi/remote/ServiceInterface.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief RequestTypeCompilation ostream
         *
         * @param out
         * @param obj
         * @return std::ostream&
         */
        std::ostream& operator<<(std::ostream& out, const RemoteService& obj) {

            out << obj._serviceType << ' ';
            out << obj._address << ' ';
            out << obj._port << ' ';
            for (auto file : obj._filenameList)
                out << file << ' ';
            out << obj._port << std::endl;

            return out;
        }

        /**
         * @brief RequestTypeCompilation istream
         *
         * @param out
         * @param obj
         * @return std::ostream&
         */
        std::istream& operator>>(std::istream& in, RemoteService& obj) {

            in >> obj._serviceType >> obj._address >> obj._port;
            while (in.good()) {
                rsi::Parameter file;
                in >> file;
                if (file != "")
                    obj._filenameList.push_back(file);
            }

            return in;
        }

        /**
         * @brief isUploader()
         *
         * @return true
         * @return false
         */
        bool RemoteService::isUploader() const {
            return extras::str::contains(_serviceType, "upload");
        }

        /**
         * @brief prepare()
         *
         * @param session
         */
        void  RemoteService::prepare(const SessionInterface& session) const {
            if (isUploader())
                for (auto file : filenames())
                    session.add(file);
        }

        /**
         * @brief cleanup()
         *
         * @param session
         */
        void  RemoteService::cleanup(const SessionInterface& session) const {
            for (auto file : filenames())
                session.remove(file);
        }


    }  // namespace rsi
}  // namespace extras
