/**
 * @file Uploader.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief UploaderInterface, Uploader class
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISERVICES_UPLOADER_CLIENT_HPP
#define _EXPARX_RSISERVICES_UPLOADER_CLIENT_HPP

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
#include <extras_rsi/service/uploader/Uploader.hpp>

namespace extras {
    namespace rsi {

        /**
         * @brief concrete class UploaderClient
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */
        concrete class UploaderClient extends Uploader with virtual SemaphoreInterface {
        protected:

            virtual Lock lock(const Lock& lock)  override;
            virtual Lock unlock(const Lock& lock)  override;
        public:
            virtual void connect() override;
            virtual void transfer() override;
            virtual void close() const override;
            virtual void send_file_block(const Filename& filename) const override;
            virtual Filename write_file_block(const Filename& filename) const override;
            virtual void send_line_block(const LinePacket& msg) const override;
            virtual LinePacket read_line_block() override;
        };

        /**
         * @brief uploader_client
         *
         * @param argc
         * @param argv
         * @return int
         */
        int uploader_client(int argc, char const* argv[]);

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_UPLOADER_CLIENT_HPP
