
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

        rsi::BinFile ConvertFile::loadBin(std::istream& in, int columns) const {
            rsi::BinFile binFile;
            rsi::ConvertLine converter;
            while (in.good()) {
                rsi::BinLine line;
                for (int i = 0; i < columns && in.good();i++) {
                    byte b = 0;
                    in >> std::noskipws >> b;
                    if (in.good())
                        line.push_back(b);
                }
                binFile.push_back(line);
            }
            return binFile;
        }
        rsi::HexFile ConvertFile::loadHex(std::istream& in) const {
            rsi::HexFile hexFile;
            rsi::ConvertLine converter;
            while (in.good()) {
                rsi::HexLine line;
                getline(in, line);
                hexFile.push_back(line);
            }
            return hexFile;

        }

        void ConvertFile::saveBin(std::ostream& out, const BinFile& binFile) const {
            for (auto binLine : binFile) {
                for (auto b : binLine)
                    out << std::skipws << b;
            }
        }
        void ConvertFile::saveHex(std::ostream& out, const HexFile& hexFile) const {
            for (auto hexLine : hexFile) {
                out << hexLine << std::endl;
            }
        }

    }
}
