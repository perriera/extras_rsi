#ifndef _EXPARX_RSISOCKETSPARAMETERS_HPP
#define _EXPARX_RSISOCKETSPARAMETERS_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <extras/interfaces.hpp>
#include <rsi/sockets/Types.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

/**
 * @brief
 *
 */

namespace extras {
    namespace rsi {

        interface SocketPoolParametersInterface {
            friend std::ostream& operator<<(std::ostream& out,
                const SocketPoolParametersInterface& obj);
            friend std::istream& operator>>(std::istream& in,
                SocketPoolParametersInterface& obj);
            virtual Parameters parameters(int argc, char const* argv[]) pure;
            virtual const Parameter& program() const pure;
            virtual const Parameter& ip() const pure;
            virtual const Parameter& port() const pure;
            virtual const Parameter& filename() const pure;
            virtual const SocketRequestTypeList& requests() const pure;

            virtual void setProgram(const Parameter& program) pure;
            virtual void setIP(const IP& ip) pure;
            virtual void setPort(const Port& port) pure;
            virtual void setFilename(const Filename& filename) pure;
            virtual void setRequests(const SocketRequestTypeList& list) pure;

            bool operator==(const SocketPoolParametersInterface& rhs) const {
                std::stringstream ssA;
                ssA << *this;
                std::string testA = ssA.str();
                std::stringstream ssB;
                ssB << rhs;
                std::string testB = ssB.str();
                return testB == testA;
            }

            bool operator!=(const SocketPoolParametersInterface& rhs) const {
                return !(*this == rhs);
            }
        };

    }
}

#endif // _EXPARX_RSISOCKETSPARAMETERS_HPP


