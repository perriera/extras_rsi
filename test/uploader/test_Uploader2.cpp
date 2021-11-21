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
static std::string packet;

class TestUploaderClient extends rsi::UploaderClient {
public:
    virtual void connect() {};
    virtual void transfer() const {
        rsi::FileNotFoundException::assertion(filename(), __INFO__);
        rsi::ParcelImploder parcelImploder;
        auto wrapped = parcelImploder.wrap(filename());
        rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        // wrapped_parcel = wrapped;
        send(wrapped);
        std::cout << extras::pass(wrapped) << std::endl;
        std::cout << extras::pass("send_file2 successful") << std::endl;
    };
    virtual void close() const {};
    virtual void send(const rsi::Filename& filename) const {
        auto cp_cmd = "cp " + filename + " " + server_dir;
        SystemException::assertion(cp_cmd, __INFO__);
    };
    virtual void write(const rsi::Filename& filename) const {
        auto cp_cmd = "cp " + filename + " " + client_dir;
        SystemException::assertion(cp_cmd, __INFO__);
    };
};

class TestUploaderServer extends rsi::UploaderServer {
public:
    virtual void connect() {};
    virtual void transfer() const {
        rsi::ParcelImploder parcelImploder;
        auto wrappedName = parcelImploder.wrapped(filename());
        write(wrappedName);
        rsi::FileNotFoundException::assertion(wrappedName, __INFO__);
        parcelImploder.unWrap(filename());
        parcelImploder.merge(filename());
        auto original = parcelImploder.clean(filename());
        auto test = fs::exists(filename());
        auto msg = (test ? "write_file successful" : "did not upload");
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(msg) << std::endl;
    };
    virtual void close() const {};
    virtual void send(const rsi::Filename& filename) const {
        auto cp_cmd = "cp " + filename + " " + client_dir;
        SystemException::assertion(cp_cmd, __INFO__);
    };
    virtual void write(const rsi::Filename& filename) const {
        auto cp_cmd = "cp " + filename + " " + server_dir;
        SystemException::assertion(cp_cmd, __INFO__);
    };
};

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

    if (fs::exists(client_dir)) {
        fs::remove_all(client_dir);
        SystemException::assertion("mkdir " + client_dir, __INFO__);
    }
    if (fs::exists(server_dir)) {
        fs::remove_all(server_dir);
        SystemException::assertion("mkdir " + server_dir, __INFO__);
    }

    REQUIRE(fs::exists(original));

    auto target1 = extras::replace_all(_filename, "data/", server_dir);
    REQUIRE(!fs::exists(target1));
    i_client.send(_filename);
    REQUIRE(fs::exists(target1));

    auto target2 = extras::replace_all(_filename, "data/", client_dir);
    REQUIRE(!fs::exists(target2));
    i_client.write(_filename);
    REQUIRE(fs::exists(target2));

    i_client.parameters(argc, argv1);
    i_server.parameters(argc, argv2);

    i_client.connect();
    i_server.connect();
    i_client.transfer();
    i_client.close();
    REQUIRE(fs::exists(original));

}
