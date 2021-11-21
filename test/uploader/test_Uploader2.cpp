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

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

class TestUploaderClient extends rsi::UploaderClient {
public:
    virtual void connect() {};
    virtual void transfer() const {};
    virtual void close() const {};
    virtual void send(const rsi::Filename& filename) const {};
    virtual void write(const rsi::Filename& filename) const {};
};

class TestUploaderServer extends rsi::UploaderServer {
public:
    virtual void connect() {};
    virtual void transfer() const {};
    virtual void close() const {};
    virtual void send(const rsi::Filename& filename) const {};
    virtual void write(const rsi::Filename& filename) const {};
};

SCENARIO("Test UploaderInterface: basic4", "[UploaderInterface]") {

    rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
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

    REQUIRE(fs::exists(original));
    i_client.parameters(argc, argv1);
    i_server.parameters(argc, argv2);

    i_client.connect();
    i_server.connect();

    i_client.transfer();
    i_client.send("filename.txt");
    i_client.write("filename.txt");
    i_client.close();
    REQUIRE(fs::exists(original));

}
