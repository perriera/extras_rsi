/**
 * @file remote/Service.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief RemoteService
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSI_REMOTESERVICE_HPP
#define _EXPARX_RSI_REMOTESERVICE_HPP

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

#include <extras/interfaces.hpp>
#include <extras_rsi/remote/ExecutableInterface.hpp>
#include <extras_rsi/remote/ServiceInterface.hpp>
#include <extras_rsi/remote/sockets/Types.hpp>
#include <extras_rsi/remote/sockets/PortAuthority.hpp>
#include <extras_rsi/remote/SessionType.hpp>
#include <extras_rsi/remote/sockets/LineBlock.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief RemoteService
         *
         */

        concrete class RemoteService implements ServiceInterface
            with ExecutableInterface {

            friend std::ostream& operator<<(std::ostream& out, const RemoteService& obj);
            friend std::istream& operator>>(std::istream& in, RemoteService& obj);

            ServiceType _serviceType;
            Parameter _address;
            Parameter _port;
            Filenames _filenameList;

            struct task_parameters {
                Filenames _filenames;
                bool _extra_files;
                Filename _filename2;
                Parameter _service;
                Parameter _address;
                Parameter _port;
                task_parameters(const ServiceInterface& si) {
                    _filenames = si.filenames();
                    _extra_files = _filenames.size() > 1;
                    _filename2 = (_extra_files ? _filenames[1] : "");
                    _service = si.service();
                    _address = si.address();
                    _port = si.port();
                }
            };

            void background_uploader(task_parameters parms);
            void background_vendor(task_parameters parms);
            void background_downloader(task_parameters parms);

        public:

            /**
             * @brief ServiceInterface
             *
             */
            virtual const ServiceType& service() const override { return _serviceType; }
            virtual const Parameter& address() const override { return _address; }
            virtual const Parameter& port() const override { return _port; }
            virtual const Filenames& filenames() const override { return _filenameList; }
            virtual bool isUploader() const override;
            virtual bool isServer(const Parameter& param) const override;
            virtual void prepare(const SessionInterface& session) const override;
            virtual void cleanup(const SessionInterface& session) const override;

            /**
             * @brief ExecutableInterface
             *
             * @param task
             */
            virtual void internal(const ServiceType& task) override;
            virtual void external(const ServiceType& task) override;

        };


    }
}

#endif // _EXPARX_RSI_SERVICE_HPP


