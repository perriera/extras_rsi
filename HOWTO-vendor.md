## HOWTO-vendor.md
This vendor utility allows the developer to quickly vendor a file, (binary or otherwise) over a socket connection. By **vendor** we mean it will perform whatever changes are necessary while the file is on the server. See the VendorServer::transfer() method for more on this. When the vendor portion is completed the updates to the file must be saved to the same file, (this allows the download_server to safely assume the filename). To make this work, the vendor utility is divided into two parts, one for the client and one for the server, (known as the **vendor_client** and **vendor_server**, respectively), (See **HOWTO-socketpool.md** for more on port allocation, synchronization and locks). 

**Note:** This utility is part of a **upload**/**vendor**/**download** trio of utilities that are designed to allow the client of a particular website to be able to upload only those files necessary for processing. Then when the vendor processing is completed the download portion of the trio will automatically restore the contents of the original zip archive with only those files that were sent for processing being altered. This ensures that client specific files, (that may contain sensitive information such sources files, SSL certificates or other files of a sensitive nature) are never uploaded to the server. In this way both the client's and the server's proprietary information is preserved and protected. It is up to the client however to verify, (and/or alter) the **isImplodable** method of the **UploaderInterface** to ensure which files will be uploaded for processing. Further, the **transfer** method of the **VendorServer** for the server portion might need customization as it will be the code running on the server itself. 

## vendor_client
The **vendor_client** utility requires the following parameters:

	vendor_client <filename> <ip> <port> | -help

Where:

 - **filename** usually refers to a zip file
 - **ip** usually refers an ip address, (in numeric IP format, not DNS format)
 - **port** is a number between 0-65535

## vendor_server
The **vendor_client** utility requires the following parameters:

	vendor_server <filename> <ip> <port> | -help

Where:

 - **filename** usually refers to a zip file
 - **ip** usually refers an ip address, (in numeric IP format, not DNS format)
 - **port** is a number between 0-65535

### -help
> Displays this help text, (provided this file is in the same directory).

## Summary
This utility was put together as a convenience. It can be installed as part of the operating system, (see INSTALL.md).


 
