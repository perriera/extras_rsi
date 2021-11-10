
#include <iostream>

#include <rsi/bin2hex/ConvertFile.hpp>

using namespace std;

// virtual const Parameter &program() const pure;
// virtual const Parameter &ip() const pure;
// virtual const Parameter &port() const pure;
// virtual const Parameter &filename() const pure;
// virtual const SocketRequestTypeList &requests() const pure;

namespace extras {
    namespace rsi {

        rsi::BinFile ConvertFile::loadBin(std::istream& in, int columns) const {}
        rsi::HexFile ConvertFile::loadHex(std::istream& in) const {}

    }
}
