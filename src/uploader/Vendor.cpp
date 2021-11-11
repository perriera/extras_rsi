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
            FileNotFoundException::assertion(theContent(), __INFO__);
            std::ifstream inBin(theContent());
            CantOpenStreamException::assertion(inBin, theContent(), __INFO__);
            std::ofstream outHex(theCourier());
            CantOpenStreamException::assertion(outHex, theContent(), __INFO__);
            rsi::ConvertFile converter;
            converter.convertToHex(inBin, outHex);
        }

        /**
         * @brief Vendor::deliverParcel
         *
         */
        void rsi::Vendor::deliverParcel() {
            auto uploaded_file =
                extras::replace_all(theCourier(), ".txt", "_uploaded.txt");
            auto listTransit = "ls -la " + theCourier();
            (void)system(listTransit.c_str());
            auto delete_cmd = "rm " + theCourier();
            (void)system(delete_cmd.c_str());
            (void)system(listTransit.c_str());
            auto move_cmd = "mv " + uploaded_file + " " + theCourier();
            (void)system(move_cmd.c_str());
            auto cat_cmd = "cat " + theCourier();
            (void)system(cat_cmd.c_str());
            (void)system(listTransit.c_str());
        }

        /**
         * @brief Vendor::unwrapParcel
         *
         */
        void rsi::Vendor::unwrapParcel() {
            FileNotFoundException::assertion(theCourier(), __INFO__);
            std::ifstream inHex(theCourier());
            CantOpenStreamException::assertion(inHex, theCourier(), __INFO__);
            std::ofstream outBin(theContent());
            CantOpenStreamException::assertion(outBin, theContent(), __INFO__);
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
