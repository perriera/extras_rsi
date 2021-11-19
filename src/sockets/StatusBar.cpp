#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/sockets/StatusBar.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>

using namespace std;

namespace extras {


    namespace rsi {

        StatusBarMsg StatusBar::bar(int count, int max) const {
            std::stringstream ss;
            ss << "[+] " << count << " / " << max << std::endl;
            return ss.str();
        }

    }  // namespace rsi
}  // namespace extras
