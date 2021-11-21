#include <rsi/uploader/Uploader.hpp>
#include <extras/strings.hpp>
#include <rsi/parcel/Wrap.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/parcel/ParcelImploder.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <rsi/exceptions.hpp>
#include <ng_imploder/imploder/Imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>
#include <extras/status/StatusLine.hpp>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

static std::string client_dir = "data/client/";
static std::string server_dir = "data/server/";
static std::string original = ~extras::Paths("data/exparx.webflow.zip");
static rsi::BinFile internet;

class TestUploaderClient extends rsi::UploaderClient {
public:
    virtual void connect() {};
    virtual void transfer() const {
        auto fn = filename();
        rsi::FileNotFoundException::assertion(filename(), __INFO__);
        send(filename());
        // rsi::ParcelImploder parcelImploder;
        // auto wrapped = parcelImploder.wrap(filename());
        // rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        // // wrapped_parcel = wrapped;
        // send(wrapped);
        // std::cout << extras::pass(wrapped) << std::endl;
        std::cout << extras::pass("send_file2 successful") << std::endl;
    };
    virtual void close() const {};
    virtual void send(const rsi::Filename& filename) const {
        ifstream in(filename);
        rsi::BinFile binFile = rsi::ConvertFile().loadBin(in);
        internet = binFile;
    };
    virtual rsi::Filename write(const rsi::Filename& filename) const {
        if (!fs::exists(client_dir)) {
            SystemException::assertion("mkdir " + client_dir, __INFO__);
        }
        if (internet.size() == 0)
            throw "Nothing to save";
        auto target = extras::replace_all(filename, "data/", client_dir);
        ofstream out(target);
        rsi::ConvertFile().saveBin(out, internet);
        internet.clear();
        return target;
    };
};

class TestUploaderServer extends rsi::UploaderServer {
public:
    virtual void connect() {};
    virtual void transfer() const {
        auto fn = filename();
        fn = write(filename());
        rsi::FileNotFoundException::assertion(fn, __INFO__);
        // rsi::ParcelImploder parcelImploder;
        // auto wrappedName = parcelImploder.wrapped(filename());
        // write(wrappedName);
        // rsi::FileNotFoundException::assertion(wrappedName, __INFO__);
        // parcelImploder.unWrap(filename());
        // parcelImploder.merge(filename());
        // auto original = parcelImploder.clean(filename());
        std::cout << extras::pass(fn) << std::endl;
        std::cout << extras::pass("write_file successful") << std::endl;
    };
    virtual void close() const {};
    virtual void send(const rsi::Filename& filename) const {
        ifstream in(filename);
        rsi::BinFile binFile = rsi::ConvertFile().loadBin(in);
        internet = binFile;
    };
    virtual rsi::Filename write(const rsi::Filename& filename) const {
        if (!fs::exists(server_dir)) {
            SystemException::assertion("mkdir " + server_dir, __INFO__);
        }
        if (internet.size() == 0)
            throw "Nothing to save";
        auto target = extras::replace_all(filename, "data/", server_dir);
        ofstream out(target);
        rsi::ConvertFile().saveBin(out, internet);
        internet.clear();
        return target;
    };
};

static void clean() {
    if (fs::exists(client_dir)) {
        fs::remove_all(client_dir);
        SystemException::assertion("mkdir " + client_dir, __INFO__);
    }
    if (fs::exists(server_dir)) {
        fs::remove_all(server_dir);
        SystemException::assertion("mkdir " + server_dir, __INFO__);
    }
}

SCENARIO("Test UploaderInterface: basic4", "[UploaderInterface]") {

    rsi::Parameter _filename = original;
    rsi::Parameter _ip = "127.0.0.1";
    rsi::Parameter _port = "9500";

    // "data/cplusplusorg.freeformjs.imploded.zip",
    //                 "127.0.0.1",
    //                 "9003",

    const char* argv1[] = { "uploader_client", _filename.c_str(), _ip.c_str(), _port.c_str(),
                              "upload",  "vendor", "download" };
    const char* argv2[] = { "uploader_server", _filename.c_str(), _ip.c_str(), _port.c_str(),
                              "upload",  "vendor", "download" };
    int argc = 7;

    TestUploaderClient client;
    TestUploaderServer server;
    rsi::UploaderInterface& i_client = client;
    rsi::UploaderInterface& i_server = server;


    REQUIRE(fs::exists(_filename));
    clean();
    {
        auto target = extras::replace_all(_filename, "data/", client_dir);
        REQUIRE(!fs::exists(target));
        i_client.send(_filename);
        i_client.write(_filename);
        REQUIRE(fs::exists(target));
    }
    clean();
    {
        auto target = extras::replace_all(_filename, "data/", server_dir);
        REQUIRE(!fs::exists(target));
        i_server.send(_filename);
        i_server.write(_filename);
        REQUIRE(fs::exists(target));
    }

    clean();

    i_client.parameters(argc, argv1);
    i_server.parameters(argc, argv2);

    i_client.connect();
    i_server.connect();

    {
        auto target = extras::replace_all(_filename, "data/", server_dir);
        REQUIRE(!fs::exists(target));
        i_client.transfer();
        REQUIRE(!fs::exists(target));
        i_server.transfer();
        REQUIRE(fs::exists(target));
    }

    i_client.close();
    i_server.close();

    REQUIRE(fs::exists(original));

}
