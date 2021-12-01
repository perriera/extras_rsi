
## HOWTO.md
This package provides automatic socket distribution  for any socket based client/server application, specifically applications that require proprietary software to be utilized remotely over a standard Linux-style socket connection. The benefits of using the package is that much of the weight of transferring a file from the client to the server and back again is done for you. All you have to do is determine what happens to the file while it is on the server. In this light, your primarily concerned about two methods that are shared between the VendorClient and VendorServer.

## VendorClient
A sample **VendorClient**::**transfer()** method is provided:

    void rsi::VendorClient::transfer() const {

        std::string msg = "vendor started";
        send_line_block(msg);
        std::string status = read_line_block();
        RemoteDiedException::assertion(status, __INFO__);
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(status) << std::endl;

    }

Where as two important methods are available for synchronization purposes:

	send_line_block();

Which will cause the transfer() method to block until it hears from it's counterpart in the **VendorServer**:

	read_line_block(msg);

Given the overhead required to transport files back and forth, the supplied **uploader/downloader** classes handle all that for you. All that is required is that in the server portion of the **VendorServer**::**transfer()**, you do everything you need to do before updating the file and ending the method using one of the block methods. The following shows an example of processing the uploaded file on the server. Notice how the **send_line_block()/read_line_block()** methods from above compliment the **read_line_block()/send_line_block()** methods below. Synchronization using these methods is not mandatory but generally a good idea, (as synchronization of this order is something that is usually a necessity):


    void rsi::VendorServer::transfer() const {

        std::string line = read_line_block();
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(line) << std::endl;

        rsi::FileNotFoundException::assertion(filename(), __INFO__);
        std::cout << extras::cyan << extras::pass(" processes file ") << std::endl;
        std::cout << extras::blue << std::endl;
        auto fn = extras::replace_all(filename(), "data/", "data/server/");
        auto cmd = "ls -la " + filename();
        SystemException::assertion(cmd, __INFO__);
        std::cout << std::endl;
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(" lists directory") << std::endl;

        std::string msg = "vendor completed";
        send_line_block(msg);

    }
    
Below you will find a brief introduction into the primary executables of this package:

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

