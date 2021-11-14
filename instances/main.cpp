#include <iostream>
#include <filesystem>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/exceptions.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>

using namespace extras;
using namespace std;
namespace fs = std::filesystem;

int main(int argc, const char** argv)
{
  if (argc < 3) {
    cout << "parcel [-pack|-unpack|-verify|-clean|-unzip] <filename>" << endl;
    return 0;
  }
  try {
    std::string option = argv[1];
    auto filename = argv[2];
    rsi::FileNotFoundException::assertion(filename, __INFO__);
    rsi::Parameter parameter = ~extras::Paths(filename);
    rsi::Parcel parcel(parameter);
    if (option == "-pack")
      parcel.pack();
    if (option == "-unpack")
      parcel.unpack();
    if (option == "-verify")
      parcel.verify_integrity();
    if (option == "-clean")
      parcel.clean();
    if (option == "-unzip") {
      string cmd = "unzip -o " + parcel.unpacked() + " -d /tmp ";
      system(cmd.c_str());
    }
    string cmd = "ls -la " + string(filename) + "* ";
    system(cmd.c_str());
  }
  catch (exception& ex) {
    cout << ex.what() << endl;
  }
  return 0;
}
