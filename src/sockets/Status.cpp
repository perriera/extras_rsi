#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/sockets/Status.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        StatusMsg StatusLine::pass(const StatusMsg& msg) const {
            std::stringstream ss;
            ss << "[+] " << msg << "." << std::endl;
            return ss.str();

        }

        StatusMsg StatusLine::fail(const StatusMsg& msg) const {
            std::stringstream ss;
            ss << "[+] " << msg << "." << std::endl;
            return ss.str();
        }

    }  // namespace rsi
}  // namespace extras
