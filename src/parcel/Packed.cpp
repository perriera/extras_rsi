#include <rsi/parcel/Packed.hpp>
#include <rsi/exceptions.hpp>
#include <iostream>
#include <fstream>

using namespace std;

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



    }  // namespace rsi
}  // namespace extras
