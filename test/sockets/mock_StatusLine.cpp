// #include <extras/status/StatusLine.hpp>
// #include <iostream>
// #include <sstream>

// #include "../unittesting/catch.hpp"
// #include "../unittesting/fakeit.hpp"

// using namespace extras;
// using namespace fakeit;

// //
// // printf("[+]File data downloaded successfully.\n");
// //

// SCENARIO("Mock StatusLineInterface", "[StatusLineInterface]") {

//     rsi::StatusLineMsg in1 = "File data downloaded successfully";
//     rsi::StatusLineMsg in2 = "Error in socket";
//     rsi::StatusLineMsg good = "[+] File data downloaded successfully.\n";
//     rsi::StatusLineMsg bad = "[-] Error in socket.\n";
//     Mock<rsi::StatusLineInterface> mock;
//     When(Method(mock, pass))
//         .AlwaysDo(
//             [&good](const rsi::StatusLineMsg& msg) {
//                 std::stringstream ss;
//                 ss << "[+] " << msg << "." << std::endl;
//                 return ss.str();
//             });
//     When(Method(mock, fail))
//         .AlwaysDo(
//             [&good](const rsi::StatusLineMsg& msg) {
//                 std::stringstream ss;
//                 ss << "[-] " << msg << "." << std::endl;
//                 return ss.str();
//             });

//     rsi::StatusLineInterface& i = mock.get();
//     REQUIRE(i.pass(in1) == good);
//     REQUIRE(i.fail(in2) == bad);
//     Verify(Method(mock, pass));
//     Verify(Method(mock, fail));
// }
