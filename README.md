
# rsi

1. Global search and replace rsi to <project_name> 
2. change directory name 'include/rsi' to 'include/<project_name>'
3. change version number using include/version.hpp
4. keep changelog in sync with include/version.hpp

###   Description
> This is a C++ library that predicts the next chess move, (based on some of the greatest chess minds in history).</br> 
> 
 >*Why would someone want to use this?*
 >
 >Anyone with an interest in AI and Machine learning might find it interesting to try and put together a predictive engine based on previous chess games, (as maintained by [chessgames.com](https://www.chessgames.com)
>
> Presently intended for Linux platforms only.
>
 # Installation
 See Installation details on  [perriera/extras](https://github.com/perriera/extras) package.

 To build & test this library:
  
     git git@github.com:perriera/rsi.git 
     cd rsi
     mkdir build
     cd build
     cmake ..
     make
     ./run-unittests
If wish to install rsi as a shared library, (but do not have any plans to uninstall it in the future) you can do the following:

	sudo make install
However, quite often you will be upgrading **rsi** so a better way to install **rsi** is by using **sudo checkinstall**.

## sudo checkinstall
Since you will be working on different versions of **rsi** it is important that you be able to make a clean uninstall, (when required) , To be able to uninstall you will need to install the Ubuntu **checkinstall** package: [here](https://help.ubuntu.com/community/CheckInstall). 

`sudo apt-get update && sudo apt-get install checkinstall`

With the **checkinstall** package installed your installation process now becomes:
    
     git git@github.com:perriera/rsi.git 
     cd rsi
     mkdir build
     cd build
     cmake ..
     make
     ./run-unittests
     sudo dpkg -r rsi
     sudo checkinstall
     
## Uninstall command
Assuming you installed **rsi** with **checkinstall** you may uninstall at any time with:

     sudo dpkg -r rsi

## PRODUCTION vs. DEBUG
Near line 57 of CMakeLists.txt you may specify a production version here:

	#
	# NOTE: add additional project options
	#

	option(RSI_PRODUCTION "Production build"  OFF)
	
## important note on using shared libraries
After installation the **rsi** library should be found in your **/usr/local/include** and your **/usr/local/lib** directories. Also, set LD_LIBRARY_PATH, (if you haven't already done so). 

     export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
     
## perriera/extras 
The **rsi** package comes bundled with other git repositories that are downloaded automatically using the CPM/Fetch_Content construct. If you wish to install any of these sub-packages directly you will have to make changes accordingly.
    
## C++ namespace support
As of version 0.1.0 the (perriera) **rsi** package now requires the use of the namespace **libdmg**.

    using namespace rsi;


##  Ubuntu PPA support 
We are in the process of setting up rsi to be deployable via a secured Ubuntu PPA. <br>
While not available yet, instructions for such PPA support would look similar to the following:

>
>  ### Adding a PPA using the command-line
>
>Make sure you have the package  **python-software-properties**  installed.
>
>**Step 1**: On the PPA's Launchpad page, look for the heading that reads "Adding this PPA to your system". Make a note of the PPA's location, which has the format  ppa:user/ppa-name.
>
> **Step 2**: Open a terminal and enter:
>
	sudo add-apt-repository ppa:user/ppa-name

> Replace  **'ppa:user/ppa-name**' with the PPA's location that you noted above.
>
> Your system will now fetch the PPA's key. This enables your system to verify that the packages in the PPA have not been interfered with since they were built.
>
> **Step 3**: Now, as a one-off, tell your system to pull down the latest list of software from each archive it knows about, including the PPA you just added:
>
> The Authentication tab lists the keys for your repositories (but not your PPAs). Note: PPAs do have keys but the system handles them automatically and they are not listed here.
>
> When you add a repository to your system's software sources the maintainer of the repository will normally tell you how to add the key.
>
> If the maintainer does not tell you how to add the key then you need to find the "key hash" of the repository in order to look up the key on a public key server. Once you know the key hash, the key can be retrieved using the command:

	gpg --keyserver [name of keyserver] --recv-keys [keyhash]
	sudo apt-get update

> Now you're ready to start installing software from the PPA!
>
 	sudo add-apt-repository ppa:admin/ppa-dmg
 	sudo apt update
	sudo apt install openssl libssl-dev libcurlpp-dev rsi
	
 
