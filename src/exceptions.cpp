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

#include <extras_arc/bin2hex/ConvertFile.hpp>
#include <extras_rsi/remote/sockets/Types.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace rsi {

        /**
         * @brief FileNotFoundException
         *
         * @param filename
         * @param ref
         */
        void FileNotFoundException::assertion(
            const Filename& filename,
            const extras::WhereAmI& ref) {
            if (!fs::exists(filename)) throw FileNotFoundException(filename, ref);
        }

        /**
         * @brief CantOpenStreamException
         *
         * @param stream
         * @param filename
         * @param ref
         */
        void CantOpenStreamException::assertion(
            const std::istream& stream,
            const Filename& filename,
            const extras::WhereAmI& ref) {
            if (!stream.good()) throw CantOpenStreamException(filename, ref);
        }

        /**
         * @brief CantOpenStreamException
         *
         * @param stream
         * @param filename
         * @param ref
         */
        void CantOpenStreamException::assertion(
            const std::ostream& stream,
            const Filename& filename,
            const extras::WhereAmI& ref) {
            if (!stream.good()) throw CantOpenStreamException(filename, ref);
        }

        /**
         * @brief RemoteBlockException
         *
         * @param response
         * @param ref
         */
        void RemoteBlockException::assertion(
            const std::string& response,
            const extras::WhereAmI& ref) {
            if (response.size() == 0) throw RemoteBlockException("no response", ref);
        }

        /**
         * @brief BadRangeFormatException
         *
         * @param range
         * @param ref
         */
        void BadRangeFormatException::assertion(
            const std::string& range,
            const extras::WhereAmI& ref) {
            auto parts = extras::split(range, '-');
            if (parts.size() != 2) throw BadRangeFormatException(range, ref);
            int from = std::stoi(parts[0]);
            int to = std::stoi(parts[1]);
            int span = to - from;
            if (to < 1) throw BadRangeFormatException(range, ref);
            if (from < 0) throw BadRangeFormatException(range, ref);
            if (to > 0xffff) throw BadRangeFormatException(range, ref);
            if (from > 0xffff) throw BadRangeFormatException(range, ref);
            if (from >= to) throw BadRangeFormatException(range, ref);
            if (span < 0 || span>0xffff) throw BadRangeFormatException(range, ref);
        }

        /**
         * @brief NotEnoughParametersException
         *
         * @param argc
         * @param minimum
         * @param ref
         */
        void NotEnoughParametersException::assertion(int argc, int minimum, const extras::WhereAmI& ref) {
            if (argc < minimum) {
                std::string msg;
                msg += argc;
                msg += " given, ";
                msg += minimum;
                msg += " expected, (at least) ";
                throw NotEnoughParametersException(msg, ref);
            }

        }

        /**
         * @brief HelpParameterException
         *
         * @param argc
         * @param argv
         * @param ref
         */
        void HelpParameterException::assertion(int argc, char const* argv[], const extras::WhereAmI& ref) {
            if (argc < 2)
                return;
            std::string helpParm;
            helpParm += argv[1];
            helpParm = extras::str::to_lower(helpParm);
            if (extras::str::starts_with(helpParm, "-help")) {
                throw HelpParameterException(helpParm, ref);
            }
        }

        void HelpParameterException::getHelp(const Filename& howto_filename) {
            FileNotFoundException::assertion(howto_filename, __INFO__);
            std::string cmd = "cat " + howto_filename + " | less ";
            SystemException::assertion(cmd.c_str(), __INFO__);
        }

    }
}  // namespace extras
