#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/vendor/v1/Vendor.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace rsi {
        /**
         * @brief Vendor::wrapParcel
         *
         */
        void rsi::Vendor::wrapParcel() {
            FileNotFoundException::assertion(payload(), __INFO__);
            std::ifstream inBin(payload());
            std::ofstream outHex(parcel());
            rsi::ConvertFile converter;
            converter.convertToHex(inBin, outHex);
            auto listTransit = "ls -la " + parcel();
            (void)system(listTransit.c_str());
        }

        /**
         * @brief Vendor::deliverParcel
         *
         */
        void rsi::Vendor::deliverParcel() {
            FileNotFoundException::assertion(parcel(), __INFO__);
            std::ifstream inHex(parcel());
            std::ofstream outBin(payload());
            rsi::ConvertFile converter;
            converter.convertToBin(inHex, outBin);
        }

        /**
         * @brief Vendor::unwrapParcel
         *
         */
        void rsi::Vendor::unwrapParcel() {
            FileNotFoundException::assertion(parcel(), __INFO__);
            std::ifstream inHex(parcel());
            std::ofstream outBin(payload());
            rsi::ConvertFile converter;
            converter.convertToBin(inHex, outBin);
        }

    }
}  // namespace extras
