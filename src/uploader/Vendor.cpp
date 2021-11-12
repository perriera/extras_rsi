#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/uploader/Vendor.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
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
            FileNotFoundException::assertion(parcel(), __INFO__);
            std::ifstream inBin(parcel());
            CantOpenStreamException::assertion(inBin, parcel(), __INFO__);
            std::ofstream outHex(payload());
            CantOpenStreamException::assertion(outHex, payload(), __INFO__);
            rsi::ConvertFile converter;
            converter.convertToHex(inBin, outHex);
        }

        /**
         * @brief Vendor::deliverParcel
         *
         */
        void rsi::Vendor::deliverParcel() {
            auto listTransit = "ls -la " + payload();
            (void)system(listTransit.c_str());
            auto delete_cmd = "rm " + payload();
            (void)system(delete_cmd.c_str());
            (void)system(listTransit.c_str());
            auto move_cmd = "mv " + payload_uploaded() + " " + payload();
            (void)system(move_cmd.c_str());
            auto cat_cmd = "cat " + payload();
            (void)system(cat_cmd.c_str());
            (void)system(listTransit.c_str());
        }

        /**
         * @brief Vendor::unwrapParcel
         *
         */
        void rsi::Vendor::unwrapParcel() {
            FileNotFoundException::assertion(payload(), __INFO__);
            std::ifstream inHex(payload());
            CantOpenStreamException::assertion(inHex, payload(), __INFO__);
            std::ofstream outBin(parcel());
            CantOpenStreamException::assertion(outBin, parcel(), __INFO__);
            rsi::ConvertFile converter;
            converter.convertToBin(inHex, outBin);
        }

        /**
         * @brief exceptions
         *
         * @param filename
         * @param ref
         */
        void FileNotFoundException::assertion(const Filename& filename, const extras::WhereAmI& ref) {
            if (!fs::exists(filename)) throw FileNotFoundException(filename, ref);
        }

        void CantOpenStreamException::assertion(const std::istream& stream, const Filename& filename, const extras::WhereAmI& ref) {
            if (!stream.good()) throw CantOpenStreamException(filename, ref);
        }

        void CantOpenStreamException::assertion(const std::ostream& stream, const Filename& filename, const extras::WhereAmI& ref) {
            if (!stream.good()) throw CantOpenStreamException(filename, ref);
        }

    }
}  // namespace extras
