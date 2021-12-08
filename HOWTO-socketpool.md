
## HOWTO-socketpool.md
This socketpool utility allows the developer to quickly and easily allocate sockets on server for use by the client. To do this the **socketpool_client** needs to know where to find the socketpool_server, (by way of ip address and port). The **socketpool_server** will be configured with the size of the socketpool and it's range. The **socketpool_client** will only know the ip:port parameters needed to know where the **socketpool_server** is in cyberspace, (or VPN). As well, the socketpool_client will indicate how many services to setup for use by the client. These will be specified on the commandline of the **socketpool_client**. The **socketpool_server** primary task is to allocate ip:port parameters for use by the **uploader**/**vendor**/**downloader** utilities. This allows the **socketpool_server** to start the server portion of those utilities and have them running before the socketpool_client can start the client portion for each requested service. This is the essence of **(perriera) extras_rsi,** (**Remote Services Invocation**).

**Note:** This utility is part of a **upload**/**vendor**/**download** trio of utilities that are designed to allow the client of a particular website to be able to upload only those files necessary for processing. Then when the vendor processing is completed the download portion of the trio will automatically restore the contents of the original zip archive with only those files that were sent for processing being altered. This ensures that client specific files, (that may contain sensitive information such sources files, SSL certificates or other files of a sensitive nature) are never uploaded to the server. In this way both the client's and the server's proprietary information is preserved and protected. It is up to the client however to verify, (and/or alter) the **isImplodable** method of the **UploaderInterface** to ensure which files will be uploaded for processing. Further, the **transfer** method of the **VendorServer** for the server portion might need customization as it will be the code running on the server itself. 

## Value Added Reseller
This package is intended for use as a base for applications. For example, the **[(perriera) ng_monitor](https://github.com/perriera/ng_monitor)** will directly inherit from this in order to make slight refinements to the classes available here, (for the purposes of synchronizing updates from [Webflow.com](https://webflow.com/ ) and the local React/Vue/Angular project). See **[(perriera) ng_monitor](https://github.com/perriera/ng_monitor)** for more on this.

## socketpool_server
This package is intended for use of a socket connection, (be that across the Internet or just between two cans of Coke and a wire). It is separated into two parts, a client and a server. In order for the client portion to work, it must have the server portion already running. The server will want to know what port numbers to use as a pool. For now, the syntax is merely two numbers separated by a hyphen. 

The **socketpool_server** utility requires the following parameters:

	socketpool_server <ip> <port> <0x0000-0xFFFF> | -help

Where:

 - **ip** usually refers an ip address, (in numeric IP format, not DNS format)
 - **port** is a number between 0-65535
 - **range** a range of ports, (separated by a hyphen).

## socketpool_client
Once the server portion is up and running the client portion can now connect to it as long as it knows the IP and PORT for the server. The function of the client portion is to upload a specified file, (usually a zip file), have that file processed then download the results as soon as the **VendorServer::transfer()** method is completed, (see VendorClient/VendorServer for an example of this). The client will expect to have upload at least one file, but can upload as many as specified on the command line. It will however, only download the first file specified, (which we can assume has been updated on the server).
. 
The **socketpool_client** utility requires the following parameters:

	socketpool_client <ip> <port> <filename> [<filename2>...] | -help

Where:

 - **ip** usually refers an ip address, (in numeric IP format, not DNS format)
 - **port** is a number between 0-65535
 - **filename** usually refers to a zip file
 - **filename2**... (one or many optional files)

**Note**: Only the first file is downloaded when the **VendorServer::transfer()** functionality has completed processing on it, (during it's stay on the server). 



### -help
> Displays this help text, (provided this file is in the same directory).

## Summary
This utility was put together as a convenience. It can be installed as part of the operating system, (see INSTALL.md).


 
