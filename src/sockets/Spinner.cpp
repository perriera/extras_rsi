#include <rsi/sockets/Spinner.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <rsi/exceptions.hpp>
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
