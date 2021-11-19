#include <rsi/sockets/StatusBar.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <fstream>

using namespace std;

namespace extras {


    namespace rsi {

        int StatusBar::linesInFile(const std::string& filename) {
            int count = 0;
            ifstream in(filename);
            while (in.good()) {
                std::string line;
                getline(in, line);
                count++;
            }
            return count;
        }

        StatusBarMsg StatusBar::bar(int count, int max) const {
            std::stringstream ss;
            ss << "\r[+] " << count + 1 << " / " << max;
            return ss.str();
        }

    }  // namespace rsi
}  // namespace extras
