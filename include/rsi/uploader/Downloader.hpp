#ifndef _EXPARX_RSISERVICES_DOWNLOADER_HPP
#define _EXPARX_RSISERVICES_DOWNLOADER_HPP

#include <extras/interfaces.hpp>
#include <rsi/uploader/Uploader.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {

        /**
         * @brief concrete class DownloaderClient
         *
         */
        concrete class DownloaderClient extends UploaderClient {
        public:
            virtual void transfer() const override;
        };

        /**
         * @brief concrete class DownloaderServer
         *
         */
        concrete class DownloaderServer extends UploaderServer {
        public:
            virtual void transfer() const override;
        };


    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_DOWNLOADER_HPP
