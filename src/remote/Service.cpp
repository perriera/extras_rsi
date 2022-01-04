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

#include <extras_rsi/remote/ServiceInterface.hpp>
#include <extras_rsi/uploader/Downloader.hpp>
#include <extras_rsi/uploader/Uploader.hpp>
#include <extras_rsi/vendor/Vendor.hpp>
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
        std::ostream& operator<<(std::ostream& out, const RemoteService& obj) {

            out << obj._serviceType << ' ';
            out << obj._address << ' ';
            out << obj._port << ' ';
            for (auto file : obj._filenameList)
                out << file << ' ';
            out << obj._port << std::endl;

            return out;
        }

        /**
         * @brief RemoteService istream
         *
         * @param out
         * @param obj
         * @return std::ostream&
         */
        std::istream& operator>>(std::istream& in, RemoteService& obj) {

            in >> obj._serviceType >> obj._address >> obj._port;
            while (in.good()) {
                rsi::Parameter file;
                in >> file;
                if (file != "")
                    obj._filenameList.push_back(file);
            }

            return in;
        }

        /**
         * @brief isUploader()
         *
         * @return true
         * @return false
         */
        bool RemoteService::isUploader() const {
            return extras::str::contains(_serviceType, "upload");
        }

        /**
         * @brief isServer()
         *
         * @param param
         * @return true
         * @return false
         */
        bool RemoteService::isServer(const Parameter& param) const {
            return extras::str::contains(param, "server");
        }

        /**
         * @brief prepare()
         *
         * @param session
         */
        void  RemoteService::prepare(const SessionInterface& session) const {
            if (isUploader())
                for (auto file : filenames())
                    session.add(file);
        }

        /**
         * @brief cleanup()
         *
         * @param session
         */
        void  RemoteService::cleanup(const SessionInterface& session) const {
            for (auto file : filenames())
                session.remove(file);
        }

        /**
         * @brief ExecutableInterface
         *
         */
        void RemoteService::internal(const ServiceType&) {
            bool extra_files = filenames().size() > 1;
            std::string filename2 = (extra_files ? filenames()[1] : "");
            const char* argv[] = {
                 service().c_str(),
                 address().c_str(),
                 port().c_str(),
                filenames()[0].c_str(),
                filename2.c_str(),
            };
            int argc = sizeof(argv) / sizeof(argv[0]);
            argc = !extra_files ? argc - 1 : argc;
            if (extras::str::contains(service(), "upload"))
                uploader_client(argc, argv);
            if (extras::str::contains(service(), "vendor"))
                vendor_client(argc, argv);
            if (extras::str::contains(service(), "download"))
                downloader_client(argc, argv);
        }

        void RemoteService::external(const ServiceType& task) {
            SystemException::assertion(task, __INFO__);
        }

    }  // namespace rsi
}  // namespace extras
