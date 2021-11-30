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
 * The above copyright notice and  this permission  notice shall be
 * included in all copies or  substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESSED  OR   IMPLIED,  INCLUDING   BUT  NOT  LIMITED  TO  THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT.  IN  NO  EVENT  SHALL EXPARX  INCORPORATED
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER  IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM, OUT  OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR  OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Except  as  contained  in this  notice, the  name of  the EXPARX
 * INCORPORATED shall not  be used in  advertising or  otherwise to
 * promote the sale, use or other dealings in this Software without
 * prior written authorization from EXPARX INCORPORATED.
 *
 * exparx.com and www.exparx.com  are domain names  registered with
 * EXPARX INCORPORATED, (other GPL-themed licenses are included).
 *
 */

#include <rsi/uploader/Uploader.hpp>
#include <extras/strings.hpp>
#include <rsi/parcel/Wrap.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/parcel/Wrap.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <rsi/exceptions.hpp>
#include <ng_imploder/imploder/Imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Mock UploaderInterface: basic2", "[UploaderInterface]") {

    rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    rsi::Parameter _program = "uploader_client";
    rsi::Parameter _filename = original;
    rsi::Parameter _ip = "127.0.0.1";
    rsi::Parameter _port = "8080";

    Mock<rsi::UploaderInterface> mock;
    const char* argv[] = { _program.c_str(), _ip.c_str(), _port.c_str(),
                            _filename.c_str(),   "upload",  "vendor", "download" };
    int argc = 7;

    When(Method(mock, program)).Return(_program);
    When(Method(mock, filename)).Return(_filename);
    When(Method(mock, ip)).Return(_ip);
    When(Method(mock, port)).Return(_port);

    When(Method(mock, parameters))
        .AlwaysDo(
            [](int, char const* []) {
                return rsi::Parameters();
            });

    When(Method(mock, connect))
        .AlwaysDo(
            []() {
            });

    When(Method(mock, transfer))
        .AlwaysDo(
            []() {
            });

    When(Method(mock, transfer))
        .AlwaysDo(
            []() {
            });

    When(Method(mock, send))
        .AlwaysDo(
            [](const rsi::Filename&) {
            });

    When(Method(mock, write))
        .AlwaysDo(
            [](const rsi::Filename&) {
                return rsi::Filename();
            });

    When(Method(mock, close))
        .AlwaysDo(
            []() {
            });

    rsi::UploaderInterface& i = mock.get();

    REQUIRE(fs::exists(original));
    REQUIRE(i.parameters(argc, argv) == rsi::Parameters());
    REQUIRE(i.program() == _program);
    REQUIRE(i.filename() == _filename);
    REQUIRE(i.ip() == _ip);
    REQUIRE(i.port() == _port);
    i.connect();
    i.transfer();
    i.send("filename.txt");
    i.write("filename.txt");
    i.close();
    REQUIRE(fs::exists(original));
    Verify(Method(mock, parameters));
    Verify(Method(mock, program));
    Verify(Method(mock, filename));
    Verify(Method(mock, ip));
    Verify(Method(mock, connect));
    Verify(Method(mock, transfer));
    Verify(Method(mock, send));
    Verify(Method(mock, write));
    Verify(Method(mock, close));
}
