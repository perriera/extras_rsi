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

#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

void printStatus(const std::string& msg);

static auto testdata = "7354dac15dbc7d3f9f4b1f8af78f7e642bcd5892aacc25f : 6c03\n"
": 7 / 9bd : 6b5d6f9a789a987c56a8c464d2cefaf34e66a3d9c9c9489c88c5547c50b548d54a36592d56a6c07f : f8f2\n"
": 8 / 9bd : 32d7d94ed4465859d88955955e4de9e5d3a9f877a5b60aefe8f30f4216a978f34ad4eaa61616a685 : 407b\n"
": 9 / 9bd : 4c7f6b6c2de4aa56154c6ee1903095c6fbb2d6a610c946166b352653f8b98697a6c1dadaca38d3c5 : 76d\n"
": a / 9bd : 5a34584a7c3626a7d566a34d9d67e2f79160af26ceab65c7a7330ccdb0057a5788496e27e4ca845c : 95ab\n"
": b / 9bd : 9938579662319fffc5bf77eadfbb56f195aebfe2dd3f4290deabdc6c551ba45c566b5d381f6393ee : 91b1\n"
": c / 9bd : d847f77029e6673c4ffc74f1eeed53da5b99c91d4dd585a62058bc2b9effdf7e3a47f9d254954a6a : f668\n"
": d / 9bd : 11c59949aea276edc2d46e7d952292158e6de7bd5399caf9300b3ac71f667f9bfe193b51aa6aa933 : 176f\n"
": e / 9bd : 1b09fac3363942b08bbcb1c57cb65890354a92d7ba522b73f3e7ace75217adb5858bb6ac6a9d64c8 : d8d6\n"
": f / 9bd : 2069758a5fde83f168a5d7892c29befcb9a930b8320679381e6d944cf9f7ba324d391e9161fcaf8a : 6867\n"
": 10 / 9bd : 663c2ae4763cb2f08767fa3df0797abf9682fd3cdb270310d3ee4117c85b35b9632bfdd00240bf04 : fa7f\n"
": 11 / 9bd : 208aada2ddc84ce0cf75c1076156222a2bb3ae94b5bcf7979bcae46a1c2238e6709e97aa923e204d : c0d4\n"
": 12 / 9bd : aacd7894c8622b118630773cda223ea6bf91aeb37de8044f26ec09b62cada27707c110182037886a : e781\n"
": 13 / 9bd : 21e2ca5c038d56ace069588cc01cb16f510bf30420ae4c66a71d44a99b04de8a8dd2eb0da721d1ca : 87cd\n"
": 1c / 9bd : d95350520dc649064c6f6101a200e8db2c223f8515068cba4acbbc825f9167ef88c7225f21223246 : eb1c\n"
": 1d / 9bd : 7481f3b75f1b81cda2e320565b8a53959f756bfbf4fb672a1fa4973bcfdc998795ab03fc2cc5fdd5 : 868\n"
": 1e / 9bd : 6a4e4b7820dd9fcf87aceb027bb1dad66496dc6ee3c3828d4";

SCENARIO("Test void printStatus(const std::string& msg);", "[ConvertInterfaceX]") {

    printStatus(testdata);

}

SCENARIO("Test void printStatus(const std::string& msg);II", "[ConvertInterfaceX]") {

    std::ifstream in("data/exparx.webflow.zip_imploded.zip_packed.txt");
    while (in.good()) {
        std::string line;
        getline(in, line);
        printStatus(line);
    }
    std::cout << "\r\ndone" << std::endl;

}