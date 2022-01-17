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

#include <extras_rsi/invocation/ng_monitor/NgMonitor.hpp>

#include <extras_arc/zipper.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <thread>

using namespace std;
namespace fs = std::filesystem;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

namespace extras {
    namespace rsi {

        /**
         * @brief parse()
         *
         * @param argc
         * @param argv
         */
        void NgMonitor::parse(int argc, char const* argv[]) {
            NotEnoughParametersException::assertion(argc, 4, __INFO__);
            _paraneters.parse(argc, argv);
            _pathname = _paraneters.filenames()[0];
            _srcDir = _paraneters.filenames()[1];
            _rsiIP = _paraneters.address();
            _rsiIP += ":";
            _rsiIP += _paraneters.port();
        }

        /**
         * @brief effect()
         *
         */
        void NgMonitor::effect() {
            auto zipFile = _srcDir + "src.zip";
            arc::Zipper zipper(zipFile, _srcDir);
            zipper.create();
            stringstream ss;
            ss << "build/ng_client " << _rsiIP << " ";
            ss << zipFile << " ";
            ss << _pathname << " ";
            auto rsiCmd = ss.str();
            SystemException::assertion(rsiCmd, __INFO__);
            zipper.append();
            reset();
        }

        /**
         * @brief reset()
         *
         */
        void NgMonitor::reset() {
            auto rmWebflow = "rm " + _pathname;
            SystemException::assertion(rmWebflow, __INFO__);
            auto rmSrcZip = "rm " + _srcDir + "src.zip";
            SystemException::assertion(rmSrcZip, __INFO__);
        }

    }  // namespace extras
}

