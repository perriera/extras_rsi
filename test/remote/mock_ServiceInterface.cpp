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

#include <extras_rsi/remote/ServiceInterface.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <sstream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;

SCENARIO("Mock RemoteServiceInterface", "[RemoteServiceInterface]") {

    const char* argv[] = {
        "build/rsi",
        "137.184.218.130:8080",
        "data/src.zip",
        "data/exparx.webflow.zip"
    };
    int argc = sizeof(argv) / sizeof(argv[0]);

    // output parameters
    rsi::ServiceTypeList request_list = {
        "upload 137.184.218.130 9000 data/src.zip",
        "upload 137.184.218.130 9001 data/exparx.webflow.zip",
        "vendor 137.184.218.130 9002 data/src.zip data/exparx.webflow.zip",
        "download 137.184.218.130 9003 data/src.zip"
    };

    rsi::ParameterList _parameterList;
    rsi::PortAuthority _portAuthority;
    rsi::ServiceTypeList _serviceTypeList;
    extras::Filenames _filenameList;

    Mock<rsi::RemoteServiceInterface> mock;
    rsi::RemoteServiceInterface& i = mock.get();
    When(Method(mock, parameters))
        .AlwaysDo(
            [&_parameterList, &_filenameList](int argc, char const* argv[]) {
                rsi::NotEnoughParametersException::assertion(argc, 3, __INFO__);
                for (auto i = 1; i < argc; i++)
                    _parameterList.push_back(argv[i]);
                for (auto i = 2; i < argc; i++)
                    _filenameList.push_back(argv[i]);
            });
    When(Method(mock, address))
        .AlwaysDo(
            [&_parameterList, &i]() {
                return extras::str::split(_parameterList[0], ':')[0];
            });
    When(Method(mock, port))
        .AlwaysDo(
            [&_parameterList, &i]() {
                return extras::str::split(_parameterList[0], ':')[1];
            });
    When(Method(mock, filenames))
        .AlwaysDo(
            [&_parameterList, &i, &_filenameList]() {
                return _filenameList;
            });
    When(Method(mock, formUploads))
        .AlwaysDo(
            [&_parameterList, &_portAuthority, &_serviceTypeList, &i]() {
                for (auto filename : i.filenames()) {
                    std::stringstream ss;
                    ss << "upload " << i.address() << ' ';
                    ss << _portAuthority.request() << ' ' << filename;
                    _serviceTypeList.push_back(ss.str());
                }
            });


    REQUIRE(_parameterList.size() == 0);
    i.parameters(argc, argv);
    REQUIRE(_parameterList.size() == 3);
    REQUIRE(i.address() == "137.184.218.130");
    REQUIRE(i.port() == "8080");
    i.formUploads();
    auto u1 = _serviceTypeList[0];

    Verify(Method(mock, parameters));
}
