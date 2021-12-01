
## HOWTO(dot)md
This package provides automatic socket distribution  for any socket based client/server application, specifically applications that require proprietary software to be utlized remotely over a standard Linux-style socket connection. 

### SocketPool
> socketpool_server
 
	build/socketpool_server 137.184.218.130 8080 send.txt

> socketpool_client

	build/socketpool_client 137.184.218.130 8080 data/exparx.webflow.zip upload vendor download 

 ### Uploader
> uploader_client

	build/uploader_client data/exparx.webflow.zip 127.0.0.1 8080 

> uploader_server

	build/uploader_server data/exparx.webflow.zip 127.0.0.1 8080 

### Vendor
> vendor_client

	build/vendor_client data/exparx.webflow.zip 127.0.0.1 8080
> vendor_server

	build/vendor_server data/exparx.webflow.zip 127.0.0.1 8080

 
 ### Downloader
> downloader_server

	build/downloader_client data/exparx.webflow.zip 127.0.0.1 8080 

 downloader_client
 
	build/downloader_server data/exparx.webflow.zip 127.0.0.1 8080 
 
 ## Uploader class
 To make this work the Uploader class provides four methods which support synchronization between the client and the server, these are as follows:
 
            /**
             * @brief send_file_block()
             *
             * Send a file across the socket but block until it has been received.
             *
             */
            virtual void send_file_block(const Filename& filename) const pure;

            /**
             * @brief send_line_block()
             *
             * Send a line of text across the socket but block until it has been received.
             *
             */
            virtual void send_line_block(const UploaderStatus& msg) const pure;

            /**
             * @brief write_file_block()
             *
             * Write a file to the local hard disk and block until it is completely recieved.
             *
             */
            virtual Filename write_file_block(const Filename& filename) const pure;

            /**
             * @brief read_line_block()
             *
             * Read a line of text from the socket and block until it is completely recieved.
             *
             */
            virtual UploaderStatus read_line_block() const pure;

