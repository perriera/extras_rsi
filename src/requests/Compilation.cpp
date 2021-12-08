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

#include <extras_rsi/socketpool/Client.hpp>
#include <extras_rsi/requests/RequestType.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
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
        std::ostream& operator<<(std::ostream& out, const RequestTypeCompilation& obj) {
            RequestTypeList list = obj.compilation();
            out << list.size() << endl;
            for (auto line : list) {
                out << line << endl;
            }
            return out;
        }

        /**
         * @brief RequestTypeCompilation istream
         *
         * @param out
         * @param obj
         * @return std::ostream&
         */
        std::istream& operator>>(std::istream& in, RequestTypeCompilation& obj) {
            int size = 0;
            in >> size;
            RequestType line;
            getline(in, line);
            RequestTypeList list;
            while (size-- > 0 && in.good()) {
                RequestType line;
                getline(in, line);
                if (in.good()) list.push_back(line);
            }
            obj.setCompilation(list);
            return in;
        }

        /**
         * @brief RequestTypeCompilation::send_line_block
         *
         */
        void RequestTypeCompilation::send_line_block(const LinePacket&) const {
            std::stringstream ss;
            ss << *this;
            std::string line = extras::replace_all(ss.str(), "\n", ";");
            send_line(line, _socket);
        }

        /**
         * @brief RequestTypeCompilation::read_line_block
         *
         */
        LinePacket RequestTypeCompilation::read_line_block() {
            std::string line = read_line(_socket);
            line = extras::replace_all(line, ";", "\n");
            std::stringstream ss;
            ss << line;
            ss >> *this;
            return ss.str();
        }

    }  // namespace rsi
}  // namespace extras
