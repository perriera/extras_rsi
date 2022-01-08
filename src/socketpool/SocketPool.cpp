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

#include <extras_rsi/prototype/socketpool/Client.hpp>
#include <extras_rsi/prototype/requests/RequestType.hpp>
#include <extras_rsi/subsystem.hpp>
#include <extras_rsi/exceptions.hpp>
#include <extras/filesystem/system.hpp>
#include <iostream>
#include <fstream>

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

        /**
         * @brief poisonedFishReceived()
         *
         * @return true
         * @return false
         */
        bool SocketPool::poisonedFishReceived(
            const PoisonedFishKey&) const {
            return true;
        }

        /**
         * @brief killServers()
         *
         */

        void NoServersToKillException::assertion(const std::string& pattern,
            const Filename& tempFile, const extras::WhereAmI& ref) {
            auto report = "ps -A | grep \"" + pattern + "\" > " + tempFile;
            try {
                SystemException::assertion(report, __INFO__);
                SystemException::assertion("cat " + tempFile, __INFO__);
            }
            catch (SystemException& ex) {
                throw NoServersToKillException(pattern, ref);
            }
        }

        void ServerNotKilledException::assertion(const std::string& word,
            const extras::WhereAmI& ref) {
            try {
                auto kill = "kill " + word;
                SystemException::assertion(kill, __INFO__);
                std::cout << "killed " << word << std::endl;
            }
            catch (SystemException& ex) {
                throw ServerNotKilledException(word, ref);
            }
        }

        void UnknownKillParametersException::assertion(const std::string& line,
            const Filename& pattern, const extras::WhereAmI& ref) {
            if (!extras::contains(line, pattern))
                throw UnknownKillParametersException(line, ref);
        }

        /**
         * @brief killServers() const
         *
         * For use by SocketPool.
         *
         */
        void SocketPool::killServers() const {
            std::string pattern = "socketpool_serv";
            killServers(pattern);
        }

        /**
         * @brief killServers()
         *
         * For the purpose of test cases.
         *
         * @param pattern, (aka. "ps -A | grep \"" + pattern + "\"")
         */
        void SocketPool::killServers(std::string pattern) {
            auto file = "/tmp/killServers.txt";
            NoServersToKillException::assertion(pattern, file, __INFO__);
            std::ifstream in(file);
            while (in.good()) {
                std::string word;
                std::string line;
                in >> word;
                getline(in, line);
                if (word != "") {
                    UnknownKillParametersException::assertion(line, pattern, __INFO__);
                    ServerNotKilledException::assertion(word, __INFO__);
                }
            }
        }

    }  // namespace rsi
}  // namespace extras
