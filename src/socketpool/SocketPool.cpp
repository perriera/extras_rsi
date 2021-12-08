/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

#include <arpa/inet.h>
#include <unistd.h>

#include <extras_rsi/socketpool/Client.hpp>
#include <extras_rsi/requests/RequestType.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/filesystem/system.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief getHelp()
         *
         * @param howto_filename
         */
        void SocketPool::getHelp(Parameter howto_filename) const {
            FileNotFoundException::assertion(howto_filename, __INFO__);
            std::string cmd = "cat " + howto_filename + " | less ";
            SystemException::assertion(cmd.c_str(), __INFO__);
        }

        /**
         * @brief parameters()
         *
         * @param argc
         * @param argv
         * @return Parameters
         */
        Parameters SocketPool::parameters(int argc, char const* argv[]) {
            if (argc > 1 && rsi::Parameter(argv[1]) == "-help")
                help();
            return _socketParaneters.parameters(argc, argv);
        }

    }  // namespace rsi
}  // namespace extras
