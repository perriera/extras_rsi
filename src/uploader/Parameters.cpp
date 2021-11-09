#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <rsi/sockets/Types.hpp>
#include <rsi/sockets/Client.hpp>
#include <rsi/sockets/RequestType.hpp>
#include <rsi/uploader/Uploader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace extras {

    /**
     * @brief abstract class Uploader
     *
     *   build/rsi_client 127.0.0.1 8080 transfer send.txt
     *   ss >> prg >> filename >> ip >> port;
     *
     */
    rsi::Parameters rsi::Uploader::parameters(int argc, char const* argv[]) {
        if (argc < 4) {
            std::cout << "params: filename ip port" << std::endl;
            throw RSIException("params: filename ip port", __INFO__);
        }
        rsi::Parameters result;
        for (int i = 0; i < argc; i++) result.push_back(argv[i]);
        _parameters = result;
        return _parameters;
    }

}  // namespace extras
