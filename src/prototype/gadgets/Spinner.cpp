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

#include <extras_rsi/prototype/gadgets/Spinner.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <fstream>

using namespace std;

namespace extras {


    namespace rsi {

        SpinnerMsg Spinner::spinner(int index) const {
            std::stringstream ss;
            std::string spinner = "+|/-\\";
            char c = spinner[index % spinner.size()];
            ss << extras::green << "\r[";
            ss << extras::yellow << c;
            ss << extras::green << "]";
            return ss.str();
        }

    }  // namespace rsi
}  // namespace extras
