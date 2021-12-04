## HOWTO-socketpool.md
This socketpool utility allows the developer to quickly and easily allocate sockets on server for use by the client. To do this the **socketpool_client** needs to know where to find the socketpool_server, (by way of ip address and port). The **socketpool_server** will be configured with the size of the socketpool and it's range. The **socketpool_client** will only know the ip:port parameters needed to know where the **socketpool_server** is in cyberspace, (or VPN). As well, the socketpool_client will indicate how many services to setup for use by the client. These will be specified on the commandline of the **socketpool_client**. The **socketpool_server** primary task is to allocate ip:port parameters for use by the **uploader**/**vendor**/**downloader** utilities. This allows the **socketpool_server** to start the server portion of those utilities and have them running before the socketpool_client can start the client portion for each requested service. This is the essence of **(perriera) extras_rsi,** (**Remote Services Invocation**).

**Note:** This utility is part of a upload/vendor/download trio of utilities that are designed to allow the client of a particular website to be able to upload only those files necessary for processing. Then when the vendor processing is completed the download portion of the trio will automatically restore the contents of the original zip archive with only those files that were sent for processing being altered. This ensures that client specific files, (that may contain sensitive information such sources files, SSL certificates or other files of a sensitive nature) are never uploaded to the server. In this way both the client's and the server's proprietary information is preserved and protected. It is up to the client however to verify, (and/or alter) the **isImplodable** method of the **UploaderInterface** to ensure which files will be uploaded for processing. Further, the **transfer** method of the **VendorServer** for the server portion might need customization as it will be the code running on the server itself. 

### Locks/Synchronization
In order for this to work each of the **uploader**/**vendor**/**downloader** utilities are encouraged to run their transfer() method in terms of synchronization using either the traditional read/write blocks and/ro the classic **SemaphoreInterface**. Please see the **UploaderInterface** for more any methods ending in the word _block, (or the **SemaphoreInterface** for the classic lock/unlock design pattern).

## socketpool_client
The **socketpool_client** utility requires the following parameters:

	socketpool_client <ip> <port> <filename> upload vendor download ... | -help

Where:

 - **filename** usually refers to a zip file
 - **ip** usually refers an ip address, (in numeric IP format, not DNS format)
 - **port** is a number between 0-65535

## socketpool_server
The **socketpool_client** utility requires the following parameters:

	socketpool_server <ip> <port> send.txt | -help

Where:

 - **filename** usually refers to a zip file
 - **ip** usually refers an ip address, (in numeric IP format, not DNS format)
 - **port** is a number between 0-65535

### -help
> Displays this help text, (provided this file is in the same directory).

## Summary
This utility was put together as a convenience. It can be installed as part of the operating system, (see INSTALL.md).


 
