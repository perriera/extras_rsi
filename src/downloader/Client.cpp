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
     * @brief DownloaderClient::lock()
     *
     * @param lock
     * @return rsi::Lock
     */
    rsi::Lock rsi::DownloaderClient::lock(const rsi::Lock& lock) const {
        rsi::ParcelImploder parcelImploder;
        auto wrappedName = parcelImploder.wrapped(lock);
        write(wrappedName);
        return lock;
    }

    /**
     * @brief DownloaderClient::unlock()
     *
     * @param lock
     * @return rsi::Lock
     */
    rsi::Lock rsi::DownloaderClient::unlock(const rsi::Lock& lock) const {
        rsi::ParcelImploder parcelImploder;
        parcelImploder.unWrap(lock);
        parcelImploder.merge(lock);
        parcelImploder.clean(lock);
        std::cout << extras::pass(lock) << std::endl;
        std::cout << extras::pass("write_file successful") << std::endl;
        std::string msg = "downloader completed";
        send_line(msg);
        return lock;
    }

    /**
     * @brief DownloaderClient::transfer()
     *
     */
    void rsi::DownloaderClient::transfer() const {
        unlock(lock(filename()));
    }

}  // namespace extras
