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

#include <extras_rsi/sockets/StatusBar.hpp>
#include <extras_rsi/sockets/Spinner.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <fstream>

using namespace std;

namespace extras {


    namespace rsi {

        int StatusBar::lastLinesInFile = 0;

        int StatusBar::linesInFile(const std::string& filename) {
            int count = 0;
            ifstream in(filename);
            while (in.good()) {
                std::string line;
                getline(in, line);
                count++;
            }
            lastLinesInFile = count;
            return count;
        }

        StatusBarMsg StatusBar::bar(int count, int max) const {
            std::stringstream ss;
            ss << spinner(count) << " ";
            ss << extras::white << std::hex << count + 1;
            ss << extras::magenta << " / ";
            ss << extras::white << std::hex << max;
            return ss.str();
        }

    }  // namespace rsi
}  // namespace extras
