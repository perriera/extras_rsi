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
         *   (See test_UploaderClient.cpp)
         *
         */
        concrete class UploaderClient extends Uploader with virtual SemaphoreInterface {
        protected:

            /**
             * @brief SemaphoreInterface
             *
             * @param lock
             * @return Lock
             */
            virtual Lock lock(const Lock& lock)  override;
            virtual Lock unlock(const Lock& lock)  override;

            /**
             * @brief FileBlockInterface
             *
             * @param filename
             */
            virtual void send_file_block(const FilePacket& filename) const override;
            virtual FilePacket write_file_block(const FilePacket& filename) const override;

            /**
             * @brief LineBlockInterface
             *
             * @param msg
             */
            virtual void send_line_block(const UploaderStatus& msg) const override;
            virtual UploaderStatus read_line_block()  override;

        public:

            /**
             * @brief UploaderInterface
             *
             */
            virtual void connect() override;
            virtual void transfer() override;
            virtual void close() const override;

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
