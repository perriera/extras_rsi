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

#include <rsi/sockets/StatusBar.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <fstream>

using namespace std;

namespace extras {


    namespace rsi {

        char rotate(int value) {
            string symbols = "|/-\\";
            int index = value % symbols.size();
            char c = symbols.at(index);
            return c;

        }

        StatusBarMsg ColorStatusBar::bar(int count, int max) const {
            std::stringstream ss;
            ss << '\r';
            ss << extras::green << '[';
            ss << extras::yellow << rotate(count);
            ss << extras::green << "] ";
            float percent = (float)count / (float)max;
            int mod = 25 * percent;
            ss << extras::magenta;
            for (int i = 0;i < mod; i++)
                ss << '*';
            ss << extras::white;
            for (int i = mod;i < 24; i++)
                ss << '.';
            return ss.str();
        }

    }  // namespace rsi
}  // namespace extras
