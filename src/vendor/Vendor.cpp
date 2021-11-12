#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/uploader/Vendor.hpp>
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
            CantOpenStreamException::assertion(inBin, payload(), __INFO__);
            std::ofstream outHex(parcel());
            CantOpenStreamException::assertion(outHex, parcel(), __INFO__);
            rsi::ConvertFile converter;
            converter.convertToHex(inBin, outHex);
        }

        /**
         * @brief Vendor::deliverParcel
         *
         */
        void rsi::Vendor::deliverParcel() {
            auto listTransit = "ls -la " + parcel();
            (void)system(listTransit.c_str());
            auto cat_cmd = "cat " + parcel();
            (void)system(cat_cmd.c_str());
            FileNotFoundException::assertion(parcel(), __INFO__);
            std::ifstream inHex(parcel());
            CantOpenStreamException::assertion(inHex, parcel(), __INFO__);
            std::ofstream outBin(payload());
            CantOpenStreamException::assertion(outBin, payload(), __INFO__);
            rsi::ConvertFile converter;
            converter.convertToBin(inHex, outBin);
            FileNotFoundException::assertion(payload(), __INFO__);
            std::ifstream inBin(payload());
            CantOpenStreamException::assertion(inBin, payload(), __INFO__);
            std::ofstream outHex(parcel());
            CantOpenStreamException::assertion(outHex, parcel(), __INFO__);
            converter.convertToHex(inBin, outHex);
        }

        /**
         * @brief Vendor::unwrapParcel
         *
         */
        void rsi::Vendor::unwrapParcel() {
            FileNotFoundException::assertion(parcel(), __INFO__);
            std::ifstream inHex(parcel());
            CantOpenStreamException::assertion(inHex, parcel(), __INFO__);
            std::ofstream outBin(payload());
            CantOpenStreamException::assertion(outBin, payload(), __INFO__);
            rsi::ConvertFile converter;
            converter.convertToBin(inHex, outBin);
        }

    }
}  // namespace extras
