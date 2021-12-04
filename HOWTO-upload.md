## HOWTO-upload.md
This upload utility allows the developer to quickly upload a file, (binary or otherwise) over a socket connection, (to a remote server). In the default version the specified file, (assumed to be a zip archive) is first imploded and then converted into hexadecimal format. If the socket parameters are correct and there is also the server portion of the upload utility is running on the server, then a successful transfer of the file should take place. To make this work, the upload utility is divided into two parts, one for the client and one for the server, (known as the **uploader_client** and **uploader_server**, respectively), (See **HOWTO-socketpool.md** for more on port allocation, synchronization and locks). 

**Note:** This utility is part of a upload/vendor/download trio of utilities that are designed to allow the client of a particular website to be able to upload only those files necessary for processing. Then when the vendor processing is completed the download portion of the trio will automatically restore the contents of the original zip archive with only those files that were sent for processing being altered. This ensures that client specific files, (that may contain sensitive information such sources files, SSL certificates or other files of a sensitive nature) are never uploaded to the server. In this way both the client's and the server's proprietary information is preserved and protected. It is up to the client however to verify, (and/or alter) the **isImplodable** method of the **UploaderInterface** to ensure which files will be uploaded for processing. Further, the **transfer** method of the **VendorServer** for the server portion might need customization as it will be the code running on the server itself. 

## uploader_client
The **uploader_client** utility requires the following parameters:

	uploader_client <filename> <ip> <port> | -help

Where:

 - **filename** usually refers to a zip file
 - **ip** usually refers an ip address, (in numeric IP format, not DNS format)
 - **port** is a number between 0-65535

## uploader_server
The **uploader_client** utility requires the following parameters:

	uploader_server <filename> <ip> <port> | -help

Where:

 - **filename** usually refers to a zip file
 - **ip** usually refers an ip address, (in numeric IP format, not DNS format)
 - **port** is a number between 0-65535

### -help
> Displays this help text, (provided this file is in the same directory).

## Summary
This utility was put together as a convenience. It can be installed as part of the operating system, (see INSTALL.md).


 
