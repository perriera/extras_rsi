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
#include <extras_rsi/remote/Service.hpp>
#include <extras_rsi/service/downloader/Client.hpp>
#include <extras_rsi/service/downloader/Server.hpp>
#include <extras_rsi/service/uploader/Uploader.hpp>
#include <extras_rsi/invocation/vendor/Client.hpp>
#include <extras_rsi/invocation/vendor/Server.hpp>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

namespace extras {
    namespace rsi {

        static Filenames _filenames;
        static bool _extra_files;
        static Filename _filename2;
        static Parameter _service;
        static Parameter _address;
        static Parameter _port;

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

        void RemoteService::background_uploader(task_parameters parms) {
            const char* argv[] = {
                 parms._service.c_str(),
                 parms._address.c_str(),
                 parms._port.c_str(),
                parms._filenames[0].c_str(),
                parms._filename2.c_str(),
            };
            int argc = sizeof(argv) / sizeof(argv[0]);
            argc = !_extra_files ? argc - 1 : argc;
            uploader_server(argc, argv);
        }

        void RemoteService::background_vendor(task_parameters parms) {
            const char* argv[] = {
                 parms._service.c_str(),
                 parms._address.c_str(),
                 parms._port.c_str(),
                parms._filenames[0].c_str(),
                parms._filename2.c_str(),
            };
            int argc = sizeof(argv) / sizeof(argv[0]);
            argc = !_extra_files ? argc - 1 : argc;
            vendor_server(argc, argv);
        }

        void RemoteService::background_downloader(task_parameters parms) {
            const char* argv[] = {
                 parms._service.c_str(),
                 parms._address.c_str(),
                 parms._port.c_str(),
                parms._filenames[0].c_str(),
                parms._filename2.c_str(),
            };
            int argc = sizeof(argv) / sizeof(argv[0]);
            argc = !_extra_files ? argc - 1 : argc;
            downloader_server(argc, argv);
        }

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
            if (extras::str::contains(service(), "server")) {
                if (extras::str::contains(service(), "upload"))
                    std::thread(&RemoteService::background_uploader, this, task_parameters(*this)).detach();
                if (extras::str::contains(service(), "vendor"))
                    std::thread(&RemoteService::background_vendor, this, task_parameters(*this)).detach();
                if (extras::str::contains(service(), "download"))
                    std::thread(&RemoteService::background_downloader, this, task_parameters(*this)).detach();
                sleep_until(system_clock::now() + seconds(1));
            }
            else {
                if (extras::str::contains(service(), "upload"))
                    uploader_client(argc, argv);
                if (extras::str::contains(service(), "vendor"))
                    vendor_client(argc, argv);
                if (extras::str::contains(service(), "download"))
                    downloader_client(argc, argv);
            }
        }

        void RemoteService::external(const ServiceType& task) {
            if (extras::str::contains(service(), "server"))
                SystemException::assertion(task + " &", __INFO__);
            else
                SystemException::assertion(task, __INFO__);

        }  // namespace rsi
    }  // namespace extras
}

