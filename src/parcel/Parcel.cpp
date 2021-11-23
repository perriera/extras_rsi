#include <rsi/parcel/Parcel.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {
    namespace rsi {

        std::ostream& operator<<(std::ostream& out, const PackedLine& obj) {
            out << " : " << std::hex << obj.lineNo();
            out << " / " << std::hex << obj.lineCount();
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
            ParcelException::assertion(c, __INFO__);
            ss >> std::hex >> obj._lineNo;
            ParcelException::assertion(obj._lineNo, __INFO__);
            ss >> std::skipws >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> std::hex >> obj._lineCount;
            ParcelException::assertion(obj._lineCount, __INFO__);
            ss >> std::skipws >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> obj._hexLine;
            ParcelException::assertion(obj._hexLine, __INFO__);
            ss >> c;
            ParcelException::assertion(c, __INFO__);
            ss >> std::hex >> obj._crc;
            ParcelException::assertion(obj._crc, obj._hexLine, __INFO__);
            return in;
        }

        void Parcel::pack() const {
            rsi::FileNotFoundException::assertion(original(), __INFO__);
            std::ifstream inBin(original());
            std::ofstream outHex(hexed());
            rsi::HexFile hexFile = rsi::ConvertFile().convertToHex(inBin, outHex);
            rsi::PackedFile packedFile;
            int cnt = 0;
            for (auto hexLine : hexFile) {
                rsi::PackedLine packedLine(++cnt, hexFile.size(), hexLine);
                packedFile.push_back(packedLine);
            }
            std::ofstream outPacked(packed());
            for (auto packedLine : packedFile)
                outPacked << packedLine << std::endl;
            outPacked.close();
            rsi::FileNotFoundException::assertion(packed(), __INFO__);
        }

        void Parcel::unpack() const {
            auto name = packed();
            rsi::FileNotFoundException::assertion(name, __INFO__);
            std::ifstream in(name);

            rsi::HexFile hexFile;
            rsi::PackedFile badCRC;

            rsi::HexFile buffer;
            while (in.good()) {
                rsi::HexLine line;
                getline(in, line);
                if (line == "JUNK")
                    break;
                if (line.size() > 0)
                    buffer.push_back(line);
            }

            for (auto text : buffer) {
                std::stringstream ss;
                ss << text;
                rsi::PackedLine line;
                try {
                    ss >> line;
                    hexFile.push_back(line.hexLine());
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                    cout << line << endl;
                    badCRC.push_back(line);
                }
            }

            if (badCRC.size() > 0)
                cout << "BadCRC count: " << badCRC.size() << endl;
            std::ofstream outHex(hexed());
            rsi::ConvertFile().saveHex(outHex, hexFile);
            outHex.close();
            std::ifstream inHex(hexed());
            std::ofstream outBin(duplicate());
            rsi::ConvertFile().convertToBin(inHex, outBin);
            outBin.close();
            rsi::FileNotFoundException::assertion(duplicate(), __INFO__);

        }

        bool Parcel::verify_integrity() const {
            rsi::FileNotFoundException::assertion(original(), __INFO__);
            rsi::FileNotFoundException::assertion(duplicate(), __INFO__);
            rsi::ParcelException::assertion(original(), duplicate(), __INFO__);
            return true;
        }

        void Parcel::merge() const {
            rsi::FileNotFoundException::assertion(duplicate(), __INFO__);
            auto from = duplicate();
            auto to = original();
            auto cmd = "cp " + from + " " + to;
            extras::SystemException::assertion(cmd, __INFO__);
            fs::remove(from);
        }

        void Parcel::clean() const {
            if (fs::exists(packed()))
                fs::remove(packed());
            if (fs::exists(hexed()))
                fs::remove(hexed());
            if (fs::exists(duplicate()))
                fs::remove(duplicate());
        }

        void Parcel::cat() const {
            rsi::FileNotFoundException::assertion(packed(), __INFO__);
            std::string cmd = "cat " + packed();
            system(cmd.c_str());
        }

        void Parcel::dir() const {
            std::string cmd = "ls -la " + original() + "*";
            system(cmd.c_str());
        }

        void Parcel::unzip() const {
            rsi::FileNotFoundException::assertion(duplicate(), __INFO__);
            string cmd = "unzip -o " + duplicate() + " -d /tmp ";
            system(cmd.c_str());
        }


    }  // namespace rsi
}  // namespace extras
