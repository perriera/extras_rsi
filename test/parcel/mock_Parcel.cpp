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

#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/system.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ParcelInterface: hexToBin", "[ParcelInterface]") {

    rsi::Parameter original = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");
    rsi::Parameter hexed = original + "_hexed";
    rsi::Parameter packed = original + "_packed";
    rsi::Parameter duplicate = original + "_unpacked";
    Mock<rsi::ParcelInterface> mock;
    When(Method(mock, original)).AlwaysReturn(original);
    When(Method(mock, hexed)).AlwaysReturn(hexed);
    When(Method(mock, packed)).AlwaysReturn(packed);
    When(Method(mock, duplicate)).AlwaysReturn(duplicate);

    When(Method(mock, pack))
        .AlwaysDo(
            [&original, &packed, &hexed]() {
                rsi::FileNotFoundException::assertion(original, __INFO__);
                std::ifstream inBin(original);
                std::ofstream outHex(hexed);
                rsi::HexFile hexFile = rsi::ConvertFile().convertToHex(inBin, outHex);
                rsi::PackedFile packedFile;
                int cnt = 0;
                for (auto hexLine : hexFile) {
                    rsi::PackedLine packedLine(++cnt, hexFile.size(), hexLine);
                    packedFile.push_back(packedLine);
                }
                std::ofstream outPacked(packed);
                for (auto packedLine : packedFile)
                    outPacked << packedLine << std::endl;
                outPacked.close();
                rsi::FileNotFoundException::assertion(packed, __INFO__);

            });

    When(Method(mock, unpack))
        .AlwaysDo(
            [&packed, &duplicate, &hexed]() {
                rsi::FileNotFoundException::assertion(packed, __INFO__);
                std::ifstream in(packed);
                rsi::HexFile hexFile;
                while (in.good()) {
                    rsi::PackedLine line;
                    in >> line;
                    if (in.good())
                        hexFile.push_back(line.hexLine());
                }
                std::ofstream outHex(hexed);
                rsi::ConvertFile().saveHex(outHex, hexFile);
                outHex.close();
                std::ifstream inHex(hexed);
                std::ofstream outBin(duplicate);
                rsi::ConvertFile().convertToBin(inHex, outBin);
                outBin.close();
                rsi::FileNotFoundException::assertion(duplicate, __INFO__);
            }
    );

    When(Method(mock, verify_integrity))
        .AlwaysDo(
            [&original, &duplicate]() {
                rsi::FileNotFoundException::assertion(original, __INFO__);
                rsi::FileNotFoundException::assertion(duplicate, __INFO__);
                rsi::ParcelException::assertion(original, duplicate, __INFO__);
                return true;
            }
    );

    When(Method(mock, merge))
        .AlwaysDo(
            [&original, &duplicate]() {
                rsi::FileNotFoundException::assertion(duplicate, __INFO__);
                auto cmd = "cp " + duplicate + " " + original;
                extras::SystemException::assertion(cmd, __INFO__);
                fs::remove(duplicate);
            }
    );

    When(Method(mock, clean))
        .AlwaysDo(
            [&hexed, &packed, &duplicate]() {
                if (fs::exists(hexed))
                    fs::remove(hexed);
                if (fs::exists(packed))
                    fs::remove(packed);
                if (fs::exists(duplicate))
                    fs::remove(duplicate);
            }
    );

    if (fs::exists(packed))
        fs::remove(packed);
    if (fs::exists(hexed))
        fs::remove(hexed);
    if (fs::exists(duplicate))
        fs::remove(duplicate);

    rsi::ParcelInterface& i = mock.get();
    REQUIRE(i.original() == original);
    REQUIRE(i.hexed() == hexed);
    REQUIRE(i.packed() == packed);
    REQUIRE(i.duplicate() == duplicate);
    REQUIRE(fs::exists(i.original()));
    REQUIRE(!fs::exists(i.hexed()));
    REQUIRE(!fs::exists(i.packed()));
    REQUIRE(!fs::exists(i.duplicate()));
    i.pack();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.hexed()));
    REQUIRE(fs::exists(i.packed()));
    REQUIRE(!fs::exists(i.duplicate()));
    i.unpack();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.hexed()));
    REQUIRE(fs::exists(i.packed()));
    REQUIRE(fs::exists(i.duplicate()));
    i.verify_integrity();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(fs::exists(i.duplicate()));
    i.merge();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(!fs::exists(i.duplicate()));
    i.clean();
    REQUIRE(fs::exists(i.original()));
    REQUIRE(!fs::exists(i.hexed()));
    REQUIRE(!fs::exists(i.packed()));
    REQUIRE(!fs::exists(i.duplicate()));
    Verify(Method(mock, pack));
    Verify(Method(mock, unpack));
    Verify(Method(mock, verify_integrity));
}
