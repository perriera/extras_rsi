// #include <rsi/uploader/Uploader.hpp>
// #include <extras/strings.hpp>
// #include <rsi/parcel/Wrap.hpp>
// #include <rsi/parcel/Parcel.hpp>
// #include <rsi/parcel/ParcelImploder.hpp>
// #include <rsi/sockets/Types.hpp>
// #include <extras/filesystem/paths.hpp>
// #include <extras/strings.hpp>
// #include <rsi/exceptions.hpp>
// #include <ng_imploder/imploder/Imploder.hpp>
// #include <iostream>
// #include <fstream>
// #include <filesystem>
// #include <extras/filesystem/system.hpp>
// #include <extras/status/StatusLine.hpp>

// #include "../unittesting/catch.hpp"
// #include "../unittesting/fakeit.hpp"

// using namespace extras;
// using namespace fakeit;
// using namespace std;
// namespace fs = std::filesystem;

// SCENARIO("Mock UploaderInterface: current", "[UploaderInterface]") {

//     rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
//     rsi::Parameter _filename = original;
//     rsi::Parameter wrapped_parcel;

//     Mock<rsi::UploaderInterface> uploader_client;
//     Mock<rsi::UploaderInterface> uploader_server;

//     When(Method(uploader_client, transfer))
//         .AlwaysDo(
//             [&_filename, &wrapped_parcel]() {
//                 rsi::Parameter parameter = ~extras::Paths(_filename);
//                 rsi::ParcelImploder parcelImploder;
//                 auto wrapped = parcelImploder.wrap(_filename);
//                 wrapped_parcel = wrapped;
//                 // extras::rsi::send_file2(wrapped, this->_sockfd);
//                 std::cout << extras::pass(wrapped) << std::endl;
//                 std::cout << extras::pass(" uploaded") << std::endl;
//             });

//     When(Method(uploader_server, transfer))
//         .AlwaysDo(
//             []() {
//                 rsi::Parameter _filename = "send.txt";
//                 rsi::ParcelImploder parcelImploder;
//                 parcelImploder.unWrap(_filename);
//                 parcelImploder.merge(_filename);
//                 auto original = parcelImploder.clean(_filename);
//                 // extras::rsi::write_file(original, this->_new_sock);
//                 std::cout << extras::pass(_filename) << std::endl;
//                 std::cout << extras::pass(" uploaded") << std::endl;
//             });


//     rsi::UploaderInterface& ic = uploader_client.get();
//     rsi::UploaderInterface& is = uploader_server.get();

//     REQUIRE(fs::exists(original));
//     ic.transfer();
//     auto cmd = "mv " + wrapped_parcel + " send.txt";
//     SystemException::assertion(cmd, __INFO__);
//     REQUIRE(fs::exists("send.txt"));
//     is.transfer();
//     REQUIRE(fs::exists(original));
//     Verify(Method(uploader_client, transfer));
//     Verify(Method(uploader_server, transfer));

//     if (fs::exists("send.txt"))
//         fs::remove("send.txt");
// }
