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
         * @brief exceptions
         *
         * @param filename
         * @param ref
         */
        void FileNotFoundException::assertion(
            const Filename& filename,
            const extras::WhereAmI& ref) {
            if (!fs::exists(filename)) throw FileNotFoundException(filename, ref);
        }

        void CantOpenStreamException::assertion(
            const std::istream& stream,
            const Filename& filename,
            const extras::WhereAmI& ref) {
            if (!stream.good()) throw CantOpenStreamException(filename, ref);
        }

        void CantOpenStreamException::assertion(
            const std::ostream& stream,
            const Filename& filename,
            const extras::WhereAmI& ref) {
            if (!stream.good()) throw CantOpenStreamException(filename, ref);
        }

    }
}  // namespace extras
