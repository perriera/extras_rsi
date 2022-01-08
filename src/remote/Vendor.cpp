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

#include <extras_rsi/remote/Vendor.hpp>
#include <extras_rsi/remote/Service.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras_rsi/sockets/SubSystem.hpp>
#include <iostream>

using namespace std;

namespace extras {
    namespace rsi {

        /**
         * @brief compile()
         *
         * @param serviceTypes
         * @param session
         * @param before
         * @return ServiceTypeList
         */
        ServiceTypeList Vendor::compile(
            const ServiceTypeMap& serviceTypes,
            const SessionInterface& session,
            const ServiceTypeList& before
        ) const {
            auto dup = serviceTypes;
            rsi::ServiceTypeList after;
            for (auto line : before) {
                std::stringstream in;
                rsi::RemoteService rs;
                in << line;
                in >> rs;
                if (!rs.isServer(dup[rs.service()]))
                    rs.prepare(session);
                std::stringstream out;
                out << dup[rs.service()] << ' ';
                out << rs.address() << ' ';
                out << rs.port() << ' ';
                for (auto file : rs.filenames())
                    out << session.entry_name(file) << ' ';
                after.push_back(out.str());
            }
            return after;
        }

        /**
         * @brief decompile()
         *
         * @param before
         * @param after
         */
        void Vendor::decompile(
            const ServiceTypeList& before,
            const ServiceTypeList& after
        ) const {
            for (size_t i = 0; i < before.size(); i++) {
                auto l1 = before[i];
                auto l2 = after[i];
                std::stringstream in1;
                std::stringstream in2;
                rsi::RemoteService rs1;
                rsi::RemoteService rs2;
                in1 << l1;
                in1 >> rs1;
                in2 << l2;
                in2 >> rs2;
                if (rs1.service() == "download") {
                    auto src = rs2.filenames()[0];
                    auto des = rs1.filenames()[0];
                    auto cpCmd = "cp " + src + " " + des + " ";
                    SystemException::assertion(cpCmd, __INFO__);
                    std::cout << white << cpCmd << yellow << " rsi update successful" << std::endl;
                };
            }
        }

        /**
         * @brief resolve()
         *
         * @param list
         * @return ServiceTypeList
         */
        ServiceTypeList Vendor::resolve(const ParametersInterface& parameters) {
            rsi::ServiceTypeList serviceTypeList;
            for (auto filename : parameters.filenames()) {
                std::stringstream ss;
                ss << "upload" << ' ' << parameters.address() << ' ';
                ss << _portAuthority.request() << ' ' << filename;
                serviceTypeList.push_back(ss.str());
            }
            {
                std::stringstream ss;
                ss << "vendor" << ' ' << parameters.address() << ' ';
                ss << _portAuthority.request() << ' ';
                for (auto filename : parameters.filenames()) {
                    ss << filename << ' ';
                }
                serviceTypeList.push_back(ss.str());
            }
            {
                std::stringstream ss;
                ss << "download" << ' ' << parameters.address() << ' ';
                ss << _portAuthority.request() << ' ';
                ss << parameters.filenames()[0];
                serviceTypeList.push_back(ss.str());
            }
            return serviceTypeList;
        }



    }  // namespace rsi
}  // namespace extras
