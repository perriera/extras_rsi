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
