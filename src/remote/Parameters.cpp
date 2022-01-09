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

#include <extras_rsi/remote/ParametersX.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief RemoteService ostream
         *
         * @param out
         * @param obj
         * @return std::ostream&
         */
        std::ostream& operator<<(std::ostream& out, const ParametersX& obj) {
            out << obj._address << ':' << obj._port << ' ';
            for (auto item : obj._filenames)
                out << item << ' ';
            return out;
        }

        /**
         * @brief RemoteService istream
         *
         * @param out
         * @param obj
         * @return std::ostream&
         */
        std::istream& operator>>(std::istream& in, ParametersX& obj) {
            rsi::Parameter address;
            in >> address;
            obj._address = extras::str::split(address, ':')[0];
            obj._port = extras::str::split(address, ':')[1];
            while (in.good()) {
                rsi::Parameter file;
                in >> file;
                if (file != "")
                    obj._filenames.push_back(file);
            }
            return in;
        }

        /**
         * @brief parameters()
         *
         * @param argc
         * @param argv
         */
        void ParametersX::parse(int argc, char const* argv[]) {
            HelpParameterException::assertion(argc, argv, __INFO__);
            NotEnoughParametersException::assertion(argc, 3, __INFO__);
            rsi::ParameterList _parameterList;
            for (auto i = 1; i < argc; i++)
                _parameterList.push_back(argv[i]);
            for (auto i = 2; i < argc; i++) {
                _filenames.push_back(argv[i]);
            }
            _address = extras::str::split(_parameterList[0], ':')[0];
            _port = extras::str::split(_parameterList[0], ':')[1];
        }

        /**
         * @brief parameters()
         *
         * @return Parameter
         */
        Parameter ParametersX::parameters() const {
            std::stringstream ss;
            for (auto param : list())
                ss << param << ' ';
            return ss.str();
        }

        /**
         * @brief list()
         *
         */
        ParameterList ParametersX::list() const {
            ParameterList list;
            Parameter param = address() + ":" + port();
            list.push_back(param);
            for (auto filename : filenames()) {
                list.push_back(filename);
            }
            return list;
        }

    }  // namespace rsi
}  // namespace extras
