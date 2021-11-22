#include <rsi/vendor/Vendor.hpp>
#include <rsi/exceptions.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/filesystem/system.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <extras/status/StatusLine.hpp>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <rsi/subsystem.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     *  @brief Vendor Client/Server ::transfer()
     *
     *  @note when this method called the time referred to in filename()
     *        is the file specified in the client portion of the code.
     *        this method is now on the server and can avail itself of
     *        whatever the server has to offer, (typically installed
     *        elsewhere and accessible via a system() call).
     *
     *        However, the file will be in 'packed' format. So, to use it
     *        you will have to unpack it, (see below).
     *
     *        This method has at least 20 seconds to get done what it has
     *        to do, (if more time is needed change the timeout value).
     *
     *        Hence it technicaly has all the time in world, (short of a
     *        power outage), to do what it needs to do.
     *
     *        When done, it has repackages the contents.
     *
     */

    void rsi::VendorServer::transfer() const {

        rsi::FileNotFoundException::assertion(filename(), __INFO__);
        std::cout << extras::cyan << extras::pass(" processes file ") << std::endl;
        std::cout << extras::blue << std::endl;
        auto fn = extras::replace_all(filename(), "data/", "data/server/");
        auto cmd = "ls -la data/server";
        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        SystemException::assertion(cmd, __INFO__);
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(" lists directory") << std::endl;

        std::string msg = "vendor completed";
        send_line(msg, this->_new_sock);

    }


}  // namespace extras
