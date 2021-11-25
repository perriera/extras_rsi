#include <rsi/uploader/Uploader.hpp>
#include <rsi/uploader/Downloader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/filesystem/paths.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <iostream>
#include <filesystem>
#include <extras/status/StatusLine.hpp>
#include <rsi/parcel/Wrap.hpp>
#include <extras/filesystem/system.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     * @brief DownloaderServer::lock()
     *
     * @param lock
     * @return rsi::Lock
     */

    rsi::Lock rsi::DownloaderServer::lock(const rsi::Lock& lock) const {
        rsi::FileNotFoundException::assertion(lock, __INFO__);
        rsi::ParcelImploder parcelImploder;
        auto wrapped = parcelImploder.wrap(lock);
        rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        send(wrapped);
        std::cout << extras::pass("send_file2 successful") << std::endl;
        return lock;
    }

    /**
     * @brief DownloaderServer::unlock()
     *
     * @param lock
     * @return rsi::Lock
     */

    rsi::Lock rsi::DownloaderServer::unlock(const rsi::Lock& lock) const {
        std::string status = read_line();
        rsi::ParcelImploder parcelImploder;
        parcelImploder.clean(lock);
        auto rm_cmd = "rm " + lock;
        SystemException::assertion(rm_cmd, __INFO__);
        RemoteDiedException::assertion(status, __INFO__);
        std::cout << extras::pass(lock) << std::endl;
        std::cout << extras::pass(status) << std::endl;
        return lock;
    }

    /**
     * @brief DownloaderServer::transfer()
     *
     */
    void rsi::DownloaderServer::transfer() const {
        unlock(lock(filename()));
    }

}  // namespace extras
