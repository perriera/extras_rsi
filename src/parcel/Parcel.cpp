#include <rsi/parcel/Parcel.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <fstream>

using namespace std;

namespace extras {
    namespace rsi {

        std::ostream& operator<<(std::ostream& out, const ParcelLine& obj) {
            out << " : " << std::hex << obj.lineNo();
            out << " : " << obj.hexLine();
            out << " : " << std::hex << obj.checksum();
            return out;
        }
        std::istream& operator>>(std::istream& in, ParcelLine& obj) {
            std::string line;
            getline(in, line);
            if (line.length() == 0)
                return in;
            stringstream ss;
            ss << line;
            char c;
            ss >> std::skipws >> c;
            ParcelLineException::assertion(c, __INFO__);
            ss >> std::hex >> obj._lineNo;
            ParcelLineException::assertion(obj._lineNo, __INFO__);
            ss >> std::skipws >> c;
            ParcelLineException::assertion(c, __INFO__);
            ss >> obj._hexLine;
            ParcelLineException::assertion(obj._hexLine, __INFO__);
            ss >> c;
            ParcelLineException::assertion(c, __INFO__);
            ss >> std::hex >> obj._crc;
            ParcelLineException::assertion(obj._crc, obj._hexLine, __INFO__);
            return in;
        }

        std::ostream& operator<<(std::ostream& out, const Parcel& obj) {
            for (auto line : obj._parcelFile)
                out << line << std::endl;
            return out;
        }

        std::istream& operator>>(std::istream& in, Parcel& obj) {
            int cnt = 0;
            obj._parcelFile.clear();
            while (in.good()) {
                rsi::ParcelLine line;
                in >> line;
                if (!in.good())
                    break;
                obj._parcelFile.push_back(line);
                rsi::ParcelLineException::assertion(++cnt, line.lineNo(), __INFO__);
            }
        }

        /**
         * @brief connect()
         * @note do whatever socket connection is required, (using the parameters
         * collected earlier)
         */
        void Parcel::pack() {
            rsi::FileNotFoundException::assertion(payload(), __INFO__);
            std::ifstream inBin(payload());
            rsi::HexFile hexFile;
            {
                std::ofstream outHex(parcel());
                rsi::ConvertFile converter;
                hexFile = converter.convertToHex(inBin, outHex);
            }
            std::ofstream outHex(parcel());
            int cnt = 0;
            _parcelFile.clear();
            for (auto hexLine : hexFile)
                _parcelFile.push_back(rsi::ParcelLine(++cnt, hexLine));
            {
                std::ofstream outHex(parcel());
                for (auto line : _parcelFile)
                    outHex << line << std::endl;
            }
            rsi::ParcelFile parcelFile2;
            {
                std::ifstream inHex(parcel());
                int cnt = 0;
                while (inHex.good()) {
                    rsi::ParcelLine line;
                    inHex >> line;
                    if (!inHex.good())
                        break;
                    parcelFile2.push_back(line);
                    rsi::ParcelLineException::assertion(++cnt, line.lineNo(), __INFO__);
                }
            }
            for (long unsigned int i = 0; i < _parcelFile.size(); i++)
                rsi::ParcelLineException::assertion(_parcelFile[i], parcelFile2[i], __INFO__);
        }

        /**
         * @brief transfer()
         * @note this is where the magic happens, depending what type of class you
         * are this method performs the data transfer, (or initiates it)
         */
        void Parcel::unpack() {
            rsi::FileNotFoundException::assertion(parcel(), __INFO__);
            rsi::ParcelFile parcelFile;
            {
                std::ifstream inHex(parcel());
                int cnt = 0;
                while (inHex.good()) {
                    rsi::ParcelLine line;
                    inHex >> line;
                    if (!inHex.good())
                        break;
                    parcelFile.push_back(line);
                    rsi::ParcelLineException::assertion(++cnt, line.lineNo(), __INFO__);
                }
            }
            //
            rsi::Parameter hexFilename = parcel() + "_hex.txt";
            {
                rsi::HexFile hexFile;
                for (auto parcelLine : parcelFile)
                    hexFile.push_back(parcelLine.hexLine());
                rsi::ConvertFile converter;
                std::ofstream outHex(hexFilename);
                converter.saveHex(outHex, hexFile);
            }
            //
            std::ifstream inBin(payload());
            rsi::ConvertFile converter;
            rsi::BinFile original = converter.loadBin(inBin);
            rsi::BinFile duplicate;
            {
                rsi::ConvertFile converter;
                std::ifstream inHex(hexFilename);
                std::ofstream outBin(payload_unpacked());
                duplicate = converter.convertToBin(inHex, outBin);
            }
            for (long unsigned int i = 0; i < original.size(); i++)
                rsi::ParcelLineException::assertion(original[i], duplicate[i], i, __INFO__);

        }

        void Parcel::compare() const {
            rsi::FileNotFoundException::assertion(payload(), __INFO__);
            rsi::FileNotFoundException::assertion(payload_unpacked(), __INFO__);
            std::ifstream before(payload());
            std::ifstream after(payload_unpacked());
            rsi::ConvertFile converter;
            rsi::BinFile a = converter.loadBin(before);
            rsi::BinFile b = converter.loadBin(after);
            for (long unsigned int i = 0; i < a.size(); i++)
                rsi::ParcelLineException::assertion(a[i], b[i], i, __INFO__);
        }

        HexFile Parcel::hexFile() const {
            HexFile hexFile;
            for (auto line : _parcelFile)
                hexFile.push_back(line.hexLine());
            return hexFile;
        }

        void Parcel::check_packaging() const {
            rsi::FileNotFoundException::assertion(parcel(), __INFO__);
            std::ifstream before(parcel());
            Parcel parcel;
            before >> parcel;
            std::ofstream packed(payload_unpacked() + "_packed");
            packed << parcel;
            HexFile hexFile = parcel.hexFile();
            std::ofstream temp_hexFile(payload_unpacked() + "_hexfile");
            rsi::ConvertFile converter;
            converter.saveHex(temp_hexFile, hexFile);
            std::ifstream temp_hexFile2(payload_unpacked() + "_hexfile");
            rsi::FileNotFoundException::assertion(payload_unpacked(), __INFO__);
            std::ofstream payload_data(payload_unpacked() + "_check_packaging");
            rsi::BinFile a = converter.convertToBin(temp_hexFile2, payload_data);
            std::ifstream payload_unpacked_(payload_unpacked());
            rsi::BinFile b = converter.loadBin(payload_unpacked_);
            for (long unsigned int i = 0; i < a.size(); i++)
                rsi::ParcelLineException::assertion(a[i], b[i], i, __INFO__);
        }


    }  // namespace rsi
}  // namespace extras
