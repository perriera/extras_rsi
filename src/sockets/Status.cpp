#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/sockets/Status.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        StatusMsg StatusLine::start(const StatusMsg& msg) const {
            auto parts = extras::split(msg, '/');
            std::stringstream ss;
            ss << "[+] " << parts[parts.size() - 1] << " started ";
            return ss.str();

        }

        StatusMsg StatusLine::pass(const StatusMsg& msg) const {
            std::stringstream ss;
            ss << "[+] " << msg << ".";
            return ss.str();

        }

        StatusMsg StatusLine::fail(const StatusMsg& msg) const {
            std::stringstream ss;
            ss << "[+] " << msg << ".";
            return ss.str();
        }

    }  // namespace rsi
}  // namespace extras
