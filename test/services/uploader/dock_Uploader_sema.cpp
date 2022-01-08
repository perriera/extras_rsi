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

#include <extras_rsi/sockets/Semaphores.hpp>
#include <extras_rsi/uploader/Uploader.hpp>
#include <extras_arc/wrap.hpp>
#include <extras_arc/bin2hex/ConvertFile.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/status/StatusLine.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/system.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "../../unittesting/catch.hpp"
#include "../../unittesting/fakeit.hpp"

using namespace extras;
using namespace std;
using namespace fakeit;
namespace fs = std::filesystem;

static std::string client_dir = "data/client/";
static std::string server_dir = "data/server/";
static const std::string original = ~extras::Paths("data/exparx.webflow.zip");

static void clean() {
    arc::Parcel parcel(original);
    parcel.clean();
    arc::ParcelImploder parcelImploder(original);
    parcelImploder.clean();
    if (fs::exists(client_dir))
        fs::remove_all(client_dir);
    if (fs::exists(server_dir))
        fs::remove_all(server_dir);
}

static void prepare() {
    clean();
    SystemException::assertion("mkdir " + client_dir, __INFO__);
    SystemException::assertion("mkdir " + server_dir, __INFO__);
    auto cp_cmd = "cp " + original + " " + client_dir;
    SystemException::assertion(cp_cmd, __INFO__);
}

SCENARIO("Dock SemaphoreInterface: Uploader", "[SemaphoreInterface]") {

    /**
     * @brief Mock<rsi::UploaderInterface> uploader;
     *
     */
    arc::BinFile internet;
    rsi::UploaderStatus status;

    Mock<rsi::LineBlockInterface> lineBlock;
    Mock<rsi::FileBlockInterface> fileBlock;

    When(Method(fileBlock, send_file_block))
        .AlwaysDo(
            [&internet](const rsi::Filename& filename) {
                ifstream in(filename);
                arc::BinFile binFile = arc::ConvertFile().loadBin(in);
                internet = binFile;
            });
    When(Method(fileBlock, write_file_block))
        .AlwaysDo(
            [&internet](const rsi::Filename& filename) {
                if (!fs::exists(server_dir)) {
                    SystemException::assertion("mkdir " + server_dir, __INFO__);
                }
                if (internet.size() == 0)
                    throw "Nothing to save";
                auto target = extras::replace_all(filename, client_dir, server_dir);
                ofstream out(target);
                arc::ConvertFile().saveBin(out, internet);
                internet.clear();
                return target;
            });
    When(Method(lineBlock, send_line_block))
        .AlwaysDo(
            [&status](const rsi::UploaderStatus& msg) {
                status = msg;
            });
    When(Method(lineBlock, read_line_block))
        .AlwaysDo(
            [&status]() {
                auto msg = status;
                status.clear();
                return msg;
            });

    // clean();
    rsi::LineBlockInterface& i_lineBlock = lineBlock.get();
    rsi::FileBlockInterface& i_fileBlock = fileBlock.get();

    /**
     * @brief Mock<rsi::SemaphoreInterface> client_lock;
     *
     */
    Mock<rsi::SemaphoreInterface> client_lock;
    When(Method(client_lock, lock))
        .AlwaysDo(
            [&i_fileBlock](const rsi::Lock& lock) {
                rsi::FileNotFoundException::assertion(lock, __INFO__);
                arc::ParcelImploder parcelImploder(lock);
                auto wrapped = parcelImploder.wrap();
                rsi::FileNotFoundException::assertion(wrapped, __INFO__);
                i_fileBlock.send_file_block(wrapped);
                return lock;
            });
    When(Method(client_lock, unlock))
        .AlwaysDo(
            [&i_lineBlock](const rsi::Lock& lock) {
                auto status = i_lineBlock.read_line_block();
                arc::ParcelImploder parcelImploder(lock);
                parcelImploder.clean();
                std::cout << extras::pass(lock) << std::endl;
                std::cout << extras::pass(status) << std::endl;
                std::cout << extras::pass("send_file2 successful") << std::endl;
                return lock;
            });

    /**
     * @brief Mock<rsi::SemaphoreInterface> client_lock;
     *
     */
    Mock<rsi::SemaphoreInterface> server_lock;
    When(Method(server_lock, lock))
        .AlwaysDo(
            [&i_fileBlock](const rsi::Lock& lock) {
                arc::ParcelImploder parcelImploder(lock);
                auto wrappedName = parcelImploder.wrapped();
                return i_fileBlock.write_file_block(wrappedName);
            });
    When(Method(server_lock, unlock))
        .AlwaysDo(
            [&i_lineBlock](const rsi::Lock& lock) {
                arc::ParcelImploder parcelImploder(lock);
                parcelImploder.unWrap();
                parcelImploder.merge();
                auto original = parcelImploder.clean();
                i_lineBlock.send_line_block("uploader completed");
                std::cout << extras::pass(lock) << std::endl;
                std::cout << extras::pass("write_file successful") << std::endl;
                return original;
            });

    /**
     * @brief Uploader Client/Server mock
     *
     */
    rsi::SemaphoreInterface& i_client = client_lock.get();
    rsi::SemaphoreInterface& i_server = server_lock.get();

    prepare();

    auto client_filename = extras::replace_all(original, "data/", client_dir);
    auto server_filename = extras::replace_all(original, "data/", server_dir);

    REQUIRE(fs::exists("data/client/exparx.webflow.zip"));
    REQUIRE(!fs::exists("data/server/exparx.webflow.zip"));

    i_client.lock(client_filename);
    i_server.lock(server_filename);
    i_server.unlock(server_filename);
    i_client.unlock(client_filename);

    REQUIRE(fs::exists("data/client/exparx.webflow.zip"));
    REQUIRE(fs::exists("data/server/exparx.webflow.zip"));

    clean();

    Verify(Method(client_lock, lock));
    Verify(Method(client_lock, unlock));
    Verify(Method(server_lock, lock));
    Verify(Method(server_lock, unlock));


}
