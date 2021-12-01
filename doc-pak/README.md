# perriera/extras_rsi
This is a C++ framework for supporting distributed features, Unix Socket programming, task management, data structures, algorithms, networking, and software design. With this framework you can easily support clients running client software on their local computers while keeping proprietary source code and data private on servers.

[![CMake](https://github.com/mattcoding4days/extras/actions/workflows/cmake.yml/badge.svg?branch=dev)](https://github.com/mattcoding4days/extras/actions/workflows/cmake.yml)

<div align="center">
  <img width="442" height="320" src="assets/extras.png">
  <br>
</div>

## Who would want to use this?
Anyone wishing to keep proprietary source code and data private but allow clients to utilize their software quickly and easily. More specifically, anyone wishing to easily coordinate multiple tasks running in the background on a remote server that can share files via Unix style sockets, will find this short little project indespensible, (as it can easily coordinate multiple tasks on remote servers from a local client).

>
> Presently intended for Linux platforms only.
>
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
     build/run-unittests-extras_rsi

## perriera/extras
The **extras_rsi** package comes bundled with **perriera/extras** package and other git repositories that are downloaded automatically using the CPM/Fetch_Content construct. If you wish to install any of these sub-packages directly you will have to make changes accordingly.
    
## C++ namespace support
As of version 0.1.0 the (perriera) **extras_rsi** package now requires the use of the namespace **extras::extras_rsi**

    using namespace extras::extras_rsi;

## CPM Optimization
> Note: Be sure to have the desired **VERSION** of perrier/extras specified in the **VERSION** keyword of the CPMAddPackage specification, (in your CMakeLists.txt). Also, to optimize CPM support on your projects be sure to set the CPM_SOURCE_CACHE environment variable for shared CPM libraries. Typically you would add this to your `.bashrc` script. With this environment variable set, the CPM package manager will not need to reload after successive build/ directory resets, (aka. `rm -rf build`). 

	export CPM_SOURCE_CACHE=$HOME/.cache/CPM

## Visual Studio Code (build/ directory) Compilation Fail Safe
The industry practice of compiling to a build/ directory is supported here. When you detect some funny business going on with your development environment, (for example if the cmake utility keeps rebuilding everything), merely delete the build/ directory, (aka. `rm -rf build`) and recreate it. If you are using the Visual Studio Code environment you can press **SHIFT-CTRL-B**, (see `.vscode/tasks.conf`) which will force a rebuild of the directory, (including re-creating `build/` for you).

> Please note: At present whenever you re-open your project with Visual Studio Code the cmake utility may or may not be in sync with the projects, (you'll notice this when all the source files keep getting rebuilt). To correct this open a Terminal window **inside** the Visual Studio Code environment and delete the build/ directory, (aka. `rm -rf build`)then rebuild the project with **SHIFT-CTRL-B**.
