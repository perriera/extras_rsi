#include <rsi/vendor/Vendor.hpp>
#include <rsi/exceptions.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/filesystem/paths.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/sockets/StatusLine.hpp>
#include <iostream>
#include <filesystem>

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

        /**
         * @brief locate the file to be unpacked
         *
         */
        rsi::Parameter parameter = ~extras::Paths(filename());
        rsi::Parcel parcel(parameter);

        /**
         * @brief unpack the file
         *
         */
        parcel.unpack();

        /**
         * @brief process the file
         *
         */
        parcel.unzip();
        parcel.dir();
        parcel.cat();

        /**
         * @brief repackage the file
         *
         */
        parcel.pack();
        parcel.dir();
        std::cout << extras::cyan;

        /**
         * @brief the packaged file will now be
         *        sent back to the client
         *
         */
        std::cout << rsi::pass(filename()) << std::endl;
        std::cout << rsi::pass(" processed") << std::endl;
    }


}  // namespace extras
