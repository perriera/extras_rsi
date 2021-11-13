#include <rsi/parcel/Parcel.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>

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

    }  // namespace rsi
}  // namespace extras
