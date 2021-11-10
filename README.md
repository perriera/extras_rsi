# perriera/extras_rsi
This is a C++ framework for supporting distributed features, Unix Socket programming, task management, data structures, algorithms, networking, and software design. With this framework you can easily support clients running client software on their local computers while keeping proprietary source code and data private on servers.
## Who would want to use this?
Anyone wishing to keep proprietary source code and data private but allow clients to utilize their software quickly and easily. 

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
     ./run-unittests-rsi

## perriera/extras
The **extras_rsi** package comes bundled with **perriera/extras** package and other git repositories that are downloaded automatically using the CPM/Fetch_Content construct. If you wish to install any of these sub-packages directly you will have to make changes accordingly.
    
## C++ namespace support
As of version 0.1.0 the (perriera) **rsi** package now requires the use of the namespace **extras::rsi**

    using namespace extras::rsi;


