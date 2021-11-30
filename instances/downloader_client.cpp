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

#include <rsi/uploader/Downloader.hpp>
#include <rsi/exceptions.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>

using namespace  extras;

int main(int argc, char const* argv[]) {
    try {
        std::cout << extras::start(argv[0]) << std::endl;
        extras::rsi::DownloaderClient downloader;
        downloader.parameters(argc, argv);
        downloader.connect();
        downloader.transfer();
        std::cout << extras::pass("File data downloaded successfully") << std::endl;
        downloader.close();
        std::cout << extras::end(argv[0]) << std::endl << std::endl;
        return 0;
    }
    catch (rsi::RSIException& ex) {
        std::cout << extras::fail(ex.what()) << std::endl << extras::end(argv[0]) << std::endl;
        std::cout << ex.getfile() << ' ' << ex.getfunc() << ' ' << ex.getline() << std::endl;
        return -1;
    }
    catch (std::exception& ex) {
        std::cout << extras::fail(ex.what()) << std::endl << extras::end(argv[0]) << std::endl;
        return -1;
    }
}
