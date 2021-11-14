#include <rsi/parcel/Parcel.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace rsi {

        std::ostream& operator<<(std::ostream& out, const PackedLine& obj) {
            out << " : " << std::hex << obj.lineNo();
            out << " : " << obj.hexLine();
            out << " : " << std::hex << obj.checksum();
            return out;
        }

        std::istream& operator>>(std::istream& in, PackedLine& obj) {
            std::string line;
            getline(in, line);
            if (line.length() == 0)
                return in;
            stringstream ss;
            ss << line;
            char c;
            ss >> std::skipws >> c;
            PackedException::assertion(c, __INFO__);
            ss >> std::hex >> obj._lineNo;
            PackedException::assertion(obj._lineNo, __INFO__);
            ss >> std::skipws >> c;
            PackedException::assertion(c, __INFO__);
            ss >> obj._hexLine;
            PackedException::assertion(obj._hexLine, __INFO__);
            ss >> c;
            PackedException::assertion(c, __INFO__);
            ss >> std::hex >> obj._crc;
            PackedException::assertion(obj._crc, obj._hexLine, __INFO__);
            return in;
        }

        void Parcel::pack() const {
            rsi::FileNotFoundException::assertion(parcel(), __INFO__);
            std::ifstream inBin(parcel());
            std::ofstream outHex(hexed());
            rsi::HexFile hexFile = rsi::ConvertFile().convertToHex(inBin, outHex);
            rsi::PackedFile packedFile;
            int cnt = 0;
            for (auto hexLine : hexFile) {
                rsi::PackedLine packedLine(++cnt, hexLine);
                packedFile.push_back(packedLine);
            }
            std::ofstream outPacked(packed());
            for (auto packedLine : packedFile)
                outPacked << packedLine << std::endl;
            outPacked.close();
            rsi::FileNotFoundException::assertion(packed(), __INFO__);
        }

        void Parcel::unpack() const {
            rsi::FileNotFoundException::assertion(packed(), __INFO__);
            std::ifstream in(packed());
            rsi::HexFile hexFile;
            rsi::PackedFile badCRC;
            while (in.good()) {
                rsi::PackedLine line;
                try {
                    in >> line;
                    if (in.good()) {
                        hexFile.push_back(line.hexLine());
                        cout << line << endl;
                    }
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                    badCRC.push_back(line);
                    in.clear(std::istream::failbit);
                }
            }
            if (badCRC.size() > 0)
                cout << "BadCRC count: " << badCRC.size() << endl;
            std::ofstream outHex(hexed());
            rsi::ConvertFile().saveHex(outHex, hexFile);
            outHex.close();
            std::ifstream inHex(hexed());
            std::ofstream outBin(unpacked());
            rsi::ConvertFile().convertToBin(inHex, outBin);
            outBin.close();
            rsi::FileNotFoundException::assertion(unpacked(), __INFO__);

        }

        void Parcel::verify_integrity() const {
            rsi::FileNotFoundException::assertion(parcel(), __INFO__);
            rsi::FileNotFoundException::assertion(unpacked(), __INFO__);
            rsi::PackedException::assertion(parcel(), unpacked(), __INFO__);
        }

        void Parcel::clean() const {
            if (fs::exists(packed()))
                fs::remove(packed());
            if (fs::exists(hexed()))
                fs::remove(hexed());
            if (fs::exists(unpacked()))
                fs::remove(unpacked());
        }


    }  // namespace rsi
}  // namespace extras
