#ifndef _EXPARX_PARCELLINE_HPP
#define _EXPARX_PARCELLINE_HPP

/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/exceptions.hpp>
#include <extras/crcs.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {
        /**
         * @brief ParcelLineInterface
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */

        using CRC = u_int16_t;

        interface ParcelLineInterface {
            virtual  int lineNo() const pure;
            virtual  int lineCount() const pure;
            virtual const HexLine& hexLine() const pure;
            virtual const CRC& checksum() const pure;

            bool operator==(const ParcelLineInterface& rhs) const {
                return hexLine() == rhs.hexLine() && checksum() == rhs.checksum();
            }

            bool operator!=(const ParcelLineInterface& rhs) const {
                return !(*this == rhs);
            }
        };

        concrete class PackedLine implements ParcelLineInterface {
            friend std::ostream& operator<<(std::ostream& out, const PackedLine& obj);
            friend std::istream& operator>>(std::istream& in, PackedLine& obj);
            int _lineNo = 0;
            int _lineCount = 0;
            HexLine _hexLine;
            CRC _crc = 0;
        public:
            PackedLine() {};
            PackedLine(int lineNo, int lineCount, const HexLine& hexLine) :
                _lineNo(lineNo), _lineCount(lineCount), _hexLine(hexLine) {
                _crc = crc16().update(_hexLine);
            };
            virtual  int lineNo() const override { return _lineNo; };
            virtual  int lineCount() const override { return _lineCount; };
            virtual const HexLine& hexLine() const override { return _hexLine; };
            virtual const CRC& checksum() const override { return _crc; };
        };

        using PackedFile = std::vector<PackedLine>;

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_PARCELLINE_HPP
