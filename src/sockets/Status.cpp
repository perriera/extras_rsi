#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/sockets/Status.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>

using namespace std;

namespace extras {


    namespace rsi {


        std::string right() {
            stringstream ss;
            ss << extras::green << '[';
            return ss.str();
        }

        std::string left() {
            stringstream ss;
            ss << extras::green << ']';
            return ss.str();
        }

        std::string status(char c) {
            stringstream ss;
            ss << right() << extras::yellow << c << left();
            return ss.str();
        }

        StatusMsg StatusLine::start(const StatusMsg& msg) const {
            auto parts = extras::split(msg, '/');
            std::stringstream ss;
            ss << status('+') << extras::cyan << " " << parts[parts.size() - 1] << " started " << extras::reset;
            return ss.str();

        }

        StatusMsg StatusLine::pass(const StatusMsg& msg) const {
            std::stringstream ss;
            ss << status('+') << extras::magenta << " " << msg << "." << extras::reset;
            return ss.str();

        }

        StatusMsg StatusLine::fail(const StatusMsg& msg) const {
            std::stringstream ss;
            ss << status('-') << extras::red << " " << msg << "." << extras::reset;
            return ss.str();
        }

    }  // namespace rsi
}  // namespace extras
