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

#include <extras_rsi/uploader/Uploader.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>

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
        if (argc == 2 && rsi::Parameter(argv[1]) == "-help")
            help();
        if (argc < 4) {
            cout << "implode <filename> <ip> <port> | -help " << endl;
            throw RSIException("params: <filename> <ip> <port>", __INFO__);
        }
        rsi::Parameters result;
        for (int i = 0; i < argc; i++) result.push_back(argv[i]);
        _parameters = result;
        return _parameters;
    }

    void rsi::Uploader::help() const {
        FileNotFoundException::assertion("HOWTO-upload.md", __INFO__);
        string cmd = "cat HOWTO-upload.md | less ";
        SystemException::assertion(cmd.c_str(), __INFO__);
    }

}  // namespace extras
