#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/sockets/StatusLine.hpp>
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

        StatusLineMsg StatusLine::start(const StatusLineMsg& msg) const {
            auto parts = extras::split(msg, '/');
            std::stringstream ss;
            ss << status('+') << extras::cyan << " " << parts[parts.size() - 1] << " started " << extras::blue;
            return ss.str();
        }

        StatusLineMsg StatusLine::end(const StatusLineMsg& msg) const {
            auto parts = extras::split(msg, '/');
            std::stringstream ss;
            ss << status('+') << extras::cyan << " " << parts[parts.size() - 1] << " completed successfully " << extras::blue;
            return ss.str();
        }

        StatusLineMsg StatusLine::pass(const StatusLineMsg& msg) const {
            std::stringstream ss;
            ss << status('+') << extras::magenta << " " << msg << "." << extras::reset;
            return ss.str();

        }

        StatusLineMsg StatusLine::fail(const StatusLineMsg& msg) const {
            std::stringstream ss;
            ss << status('-') << extras::red << " " << msg << "." << extras::reset;
            return ss.str();
        }

    }  // namespace rsi
}  // namespace extras
