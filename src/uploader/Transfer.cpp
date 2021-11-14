#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/uploader/Uploader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <extras/filesystem/paths.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <iostream>
#include <filesystem>

#include <chrono>
#include <thread>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     * @brief UploaderClient::transfer()
     *
     */
    void rsi::UploaderClient::transfer() const {
        rsi::Parameter parcel = ~extras::Paths(filename());
        rsi::Parcel packed(parcel);
        packed.pack();
        extras::rsi::send_file2(packed.packed().c_str(), this->_sockfd);
    }

    /**
     * @brief UploaderServer::transfer()
     *
     */
    void rsi::UploaderServer::transfer() const {
        cout << "\n\n\n\n\n\n" << "UploaderServer" << "\n\n\n\n\n\n";

        rsi::Parameter parcel = ~extras::Paths(filename());
        rsi::Parcel packed(parcel);
        packed.clean();
        std::string uploaded_file = packed.packed();
        cout << uploaded_file << " written" << endl;
        extras::rsi::write_file(uploaded_file.c_str(), this->_new_sock);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // try {
        //     // system("cat send.txt_packed   ");
        //     packed.unpack();
        //     system("unzip -o send.txt_unpacked -d /tmp ");
        // }
        // catch (rsi::PackedException& ex) {
        //     cout << ex.what() << endl;
        // }
        // system("ls -la");
        // /**
        //  * @brief Right here, Right now...
        //  *
        //  */
        // system("ls send* -la");
        // auto delete_cmd = "rm send.txt";
        // system(delete_cmd);
        // system("ls send* -la");
        // auto copy_cmd = "cp " + uploaded_file + " send.txt";
        // system(copy_cmd.c_str());
        // //        // auto cat_cmd = "cat send.txt";
        //        // system(cat_cmd);
        system("ls send* -la");
    }

    void rsi::VendorClient::transfer() const {
    }

    void rsi::VendorServer::transfer() const {
        try {
            cout << "\n\n\n\n\n\n" << "VendorServer" << "\n\n\n\n\n\n";
            rsi::Parameter parameter = ~extras::Paths(filename());
            rsi::Parcel parcel(parameter);
            std::string cmd = "cat " + parcel.packed();
            system(cmd.c_str());
            parcel.unpack();
            cmd = "unzip -o " + parcel.unpacked() + " -d /tmp ";
            system(cmd.c_str());
            // auto copy_cmd = "cp " + parcel.packed() + " send.txt";
            // system(copy_cmd.c_str());
            parcel.pack();
            system("ls send* -la");
        }
        catch (rsi::PackedException& ex) {
            cout << ex.what() << endl;
        }
    }

    /**
     * @brief DownloaderClient::transfer()
     *
     */
    void rsi::DownloaderClient::transfer() const {
        rsi::Parameter parcel = ~extras::Paths(filename());
        rsi::Parcel packed(parcel);
        std::string downloaded_file = packed.packed();
        extras::rsi::write_file(downloaded_file.c_str(), this->_sockfd);
        extras::rsi::send_line("Thank you", this->_sockfd);
        try {
            packed.unpack();
            auto cmd = "unzip -o " + packed.unpacked() + " -d /tmp ";
            system(cmd.c_str());
        }
        catch (rsi::PackedException& ex) {
            cout << ex.what() << endl;
        }
    }

    /**
     * @brief DownloaderServer::transfer()
     *
     */
    void rsi::DownloaderServer::transfer() const {
        cout << "\n\n\n\n\n\n" << "DownloaderServer" << "\n\n\n\n\n\n";
        rsi::Parameter parcel = ~extras::Paths(filename());
        rsi::Parcel packed(parcel);
        // packed.pack();
        std::string downloaded_file = packed.packed();
        auto copy_cmd = "cp " + downloaded_file + " send.txt";
        system(copy_cmd.c_str());
        extras::rsi::send_file2(downloaded_file.c_str(), this->_new_sock);
        auto msg = extras::rsi::read_line(this->_sockfd);
        cout << msg << endl;
        if (msg != "Thank you")
            cout << "\n\n\n\n\n\n\n\n\n\nDIDNT WORK\n\n\n\n\n\n\n" << endl;
    }

}  // namespace extras
