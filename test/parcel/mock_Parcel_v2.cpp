#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/parcel/v2/Parcel.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <rsi/exceptions.hpp>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
namespace fs = std::filesystem;

SCENARIO("Mock ParcelInterface: hexToBin (v2)", "[ParcelInterface]") {

    rsi::Parameter parcel = ~extras::Paths("data/cplusplusorg.freeformjs.imploded.zip");
    rsi::Parameter parcel_packed = parcel + "_packed";
    rsi::Parameter parcel_unpacked = parcel + "_unpacked";
    rsi::ParcelFile parcelFile;
    Mock<rsi::ParcelInterface> mock;
    When(Method(mock, parcel)).Return(parcel);
    When(Method(mock, parcel)).Return(parcel_packed);
    When(Method(mock, parcel)).Return(parcel_unpacked);
    When(Method(mock, pack))
        .AlwaysDo(
            [&parcel, &parcel_packed]() {
                rsi::FileNotFoundException::assertion(parcel, __INFO__);

            });

    When(Method(mock, unpack))
        .AlwaysDo(
            [&parcel, &parcel_unpacked]() {
                rsi::FileNotFoundException::assertion(parcel, __INFO__);
            }
    );

    if (fs::exists(parcel_packed))
        fs::remove(parcel_packed);
    if (fs::exists(parcel_unpacked))
        fs::remove(parcel_unpacked);

    rsi::ParcelInterface& i = mock.get();
    REQUIRE(fs::exists(parcel));
    REQUIRE(!fs::exists(parcel_packed));
    REQUIRE(!fs::exists(parcel_unpacked));
    i.pack();
    i.unpack();
    Verify(Method(mock, pack));
}
