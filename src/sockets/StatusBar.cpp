#include <rsi/sockets/StatusBar.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <rsi/exceptions.hpp>
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
            std::string spinner = "|/-\\";
            char c = spinner[count % spinner.size()];
            if (count > max - 2)
                c = '+';
            ss << "\r[" << c << "] " << count + 1 << " / " << max;
            return ss.str();
        }

    }  // namespace rsi
}  // namespace extras
