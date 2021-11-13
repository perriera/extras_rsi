#include <rsi/parcel/Packed.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace rsi {

        void PackedException::assertion(const Filename& packed, const Filename& unpacked, const extras::WhereAmI& ref) {
            auto cmd = "xxd " + packed + " /tmp/b1.hex";
            (void)system(cmd.c_str());
            cmd = "xxd " + unpacked + " /tmp/b2.hex";
            (void)system(cmd.c_str());
            std::string outFile = "/tmp/out.txt";
            cmd = "diff /tmp/b1.hex /tmp/b2.hex >" + outFile;
            (void)system(cmd.c_str());
            if (!fs::exists(outFile) || fs::file_size(outFile) != 0)
                throw PackedException("Files are different: (see /tmp/out.txt)", ref);
        }

    }  // namespace rsi
}  // namespace extras
