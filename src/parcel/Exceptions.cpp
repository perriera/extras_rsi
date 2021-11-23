#include <rsi/parcel/Parcel.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace rsi {

        void ParcelException::assertion(const Filename& parcel, const Filename& unpacked, const extras::WhereAmI& ref) {
            rsi::FileNotFoundException::assertion(parcel, ref);
            rsi::FileNotFoundException::assertion(unpacked, ref);
            auto cmd = "xxd " + parcel + " /tmp/b1.hex";
            (void)system(cmd.c_str());
            cmd = "xxd " + unpacked + " /tmp/b2.hex";
            (void)system(cmd.c_str());
            std::string outFile = "/tmp/out.txt";
            cmd = "diff /tmp/b1.hex /tmp/b2.hex >" + outFile;
            (void)system(cmd.c_str());
            if (!fs::exists(outFile) || fs::file_size(outFile) != 0)
                throw ParcelException("Files are different: (see /tmp/out.txt)", ref);
        }

    }  // namespace rsi
}  // namespace extras
