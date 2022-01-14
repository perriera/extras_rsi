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

#include <extras_rsi/service/uploader/Uploader.hpp>
#include <extras_rsi/remote/sockets/SubSystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <extras/status/StatusLine.hpp>
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
        HelpParameterException::assertion(argc, argv, __INFO__);
        rsi::Parameters result;
        for (int i = 0; i < argc; i++) result.push_back(argv[i]);
        _parameters = result;
        for (int i = 4; i < argc; i++) _extra_files.push_back(argv[i]);
        return _parameters;
    }

}  // namespace extras
