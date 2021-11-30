
# perriera/extras_rsi
This is a C++ framework for supporting distributed features, Unix Socket programming, task management, data structures, algorithms, networking, and software design. With this framework you can easily support clients running client software on their local computers while keeping proprietary source code and data private on servers.

[![CMake](https://github.com/mattcoding4days/extras/actions/workflows/cmake.yml/badge.svg?branch=dev)](https://github.com/mattcoding4days/extras/actions/workflows/cmake.yml)

<div align="center">
  <img width="442" height="320" src="assets/extras.png">
  <br>
</div>

## Who would want to use this?
Anyone wishing to keep proprietary source code and data private but allow clients to utilize their software quickly and easily. More specifically, anyone wishing to easily coordinate multiple tasks running in the background on a remote server that can share files via Unix style sockets, will find this short little project indispensable, (as it can easily coordinate multiple tasks on remote servers from a local client).

>
> Presently intended for Linux platforms only.
>

This framework is intended to allow developers to maintain proprietary code on servers but make it easy for clients to access those services. For example, in the case of FreeFormJS.org we would allow the Angular developer to download, compile and run their version of the extras_rsi library but the server portion of that library would remain in the server. 

The general idea is to upload a file from the client to the server, process that file and then download it again.

	build/socketpool_client 137.184.218.130 8080 data/exparx.webflow.zip upload vendor download 

Where your server, (either on a VPN or some place in cyberspace) would be running the following:

	build/socketpool_server 137.184.218.130 8080 send.txt
When executed the following should appear:

	[+] socketpool_server started 
	[+] Server socket created successfully.
	[+] Binding successfull.
	[+] Listening.

When the client side of the package is run the following will appear on the server:

	[+] uploader_server started 
	[+] Server socket created successfully.
	[+] Server socket times out in 60 seconds.
	[+] Binding successfull.
	[+] Listening.
	
	[+] vendor_server started 
	[+] Server socket created successfully.
	[+] Server socket times out in 60 seconds.
	[+] Binding successfull.
	[+] Listening.
	
	[+] downloader_server started 
	[+] Server socket created successfully.
	[+] Server socket times out in 60 seconds.
	[+] Binding successfull.
	[+] Listening.
	
	[+] data/exparx.webflow.zip_imploded.zip_packed.txt received intact
	[+] data/exparx.webflow.zip.
	[+] write_file successful.
	[+] File data uploaded successfully.
	[+] uploader_server ended 

	[+] data/exparx.webflow.zip.
	[+] vendor started.
	[+]  processes file .

	-rw-rw-r-- 1 webhost webhost 99718 Nov 30 01:52 data/exparx.webflow.zip

	[+] data/exparx.webflow.zip.
	[+]  lists directory.
	[+] File data processed successfully.
	[+] vendor_server ended 

	[+] data/exparx.webflow.zip_imploded.zip_packed.txt sent intact
	[+] send_file2 successful.
	[+] data/exparx.webflow.zip.
	[+] downloader completed.
	[+] File data downloaded successfully.
	[+] downloader_server ended 

Where as the client will see the following:

	perry@ubuntu:~/Projects/extras_rsi$ build/socketpool_client 137.184.218.130 8080 data/exparx.webflow.zip upload vendor download 
	
	[+] socketpool_client started 
	[+] Server socket created successfully.
	[+] Connected to Server.
	
	[+] uploader_client started 
	[+] Server socket created successfully.
	[+] Connected to Server.
	[+] data/exparx.webflow.zip_imploded.zip_packed.txt sent intact
	[+] data/exparx.webflow.zip.
	[+] uploader completed.
	[+] send_file2 successful.
	[+] File data uploaded successfully.
	[+] uploader_client ended 

	[+] vendor_client started 
	[+] Server socket created successfully.
	[+] Connected to Server.
	[+] data/exparx.webflow.zip.
	[+] vendor completed.
	[+] File data processed successfully.
	[+] vendor_client ended 

	[+] downloader_client started 
	[+] Server socket created successfully.
	[+] Connected to Server.
	[+] data/exparx.webflow.zip_imploded.zip_packed.txt received intact
	[+] data/exparx.webflow.zip.
	[+] write_file successful.
	[+] File data downloaded successfully.
	[+] downloader_client ended 

	-rw-rw-r-- 1 perry perry 2561859 Nov 29 17:52 data/exparx.webflow.zip

	[+] File sockets allocated successfully.
	[+] socketpool_client ended 



This project was inspired by the requirements of `ng-monitor 2.0` of `FreeFormJS.org` whereby it was necessary to strip a zip archive of all the unnecessary image and script files, upload the remaining HTML/CSS, have that HTML/CSS processed with custom Angular html tags, then finally downloaded again. All in the span of just a few moments. However, the `(perriera) extras-rsi` package can be easily adapted to any application needing to protect proprietary code.
 
 # Installation
 See Installation details on  [perriera/extras_rsi](https://github.com/perriera/extras_rsi.git) package.

 To build & test this library:
  
     git clone https://github.com/perriera/extras_rsi.git
     cd extras_rsi
     mkdir build
     cd build
     cmake ..
     make
     cd ..
     build/run-unittests-rsi

## perriera/extras
The **extras_rsi** package comes bundled with **perriera/extras** package and other git repositories that are downloaded automatically using the CPM/Fetch_Content construct. If you wish to install any of these sub-packages directly you will have to make changes accordingly.
    
## C++ namespace support
As of version 0.1.0 the (perriera) **rsi** package now requires the use of the namespace **extras::rsi**

    using namespace extras::rsi;

## CPM Optimization
> Note: Be sure to have the desired **VERSION** of perrier/extras specified in the **VERSION** keyword of the CPMAddPackage specification, (in your CMakeLists.txt). Also, to optimize CPM support on your projects be sure to set the CPM_SOURCE_CACHE environment variable for shared CPM libraries. Typically you would add this to your `.bashrc` script. With this environment variable set, the CPM package manager will not need to reload after successive build/ directory resets, (aka. `rm -rf build`). 

	export CPM_SOURCE_CACHE=$HOME/.cache/CPM

## Visual Studio Code (build/ directory) Compilation Fail Safe
The industry practice of compiling to a build/ directory is supported here. When you detect some funny business going on with your development environment, (for example if the cmake utility keeps rebuilding everything), merely delete the build/ directory, (aka. `rm -rf build`) and recreate it. If you are using the Visual Studio Code environment you can press **SHIFT-CTRL-B**, (see `.vscode/tasks.conf`) which will force a rebuild of the directory, (including re-creating `build/` for you).

> Please note: At present whenever you re-open your project with Visual Studio Code the cmake utility may or may not be in sync with the projects, (you'll notice this when all the source files keep getting rebuilt). To correct this open a Terminal window **inside** the Visual Studio Code environment and delete the build/ directory, (aka. `rm -rf build`)then rebuild the project with **SHIFT-CTRL-B**.
