
# Changelog
> All notable changes to this project will be documented in this file.</br>
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), 
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).</br>
> To add a tag to the git repository do:
> > git tag -a v3.0.1 -m "Added semaphores"</br>
> > git push origin v3.0.1
> 

IMPORTANT: 
- Manually keep the changelog version number in sync with CMakeLists.txt project version.<br>
- Keep the changelog.md up to date, neat and tidy, (as it is a convenient tool for code maintenance).<br>
- Use [Semantic Versioning](https://semver.org/spec/v2.0.0.html) such that<br>
- Given a version number MAJOR.MINOR.PATCH, increment the:<br>
- MAJOR version when you make incompatible API changes,<br>
- MINOR version when you add functionality in a backwards compatible manner, and<br>
- PATCH version when you make backwards compatible bug fixes. <br>
- But there is no need to change the version number for correcting spelling errors, (etc).<br>
- MAKE SURE to tag and update the tag compare list below, (for quick code comparison purposes).<br>

## [Unreleased]
Detailed test cases</br>
Detailed class descriptions in README.md</br>
Correct URL for github, (for source compare)</br>

## [Next Steps]
Adding mock test cases </br>
Adding unit test cases </br>
Updated README.md accordinging</br>

#### 3.0.1 (2021-11-22)
## Changed  
- Added semaphores, (better synchronization)

#### 3.0.0 (2021-11-22)
## Added  
- Working prototype

#### 2.17.0 (2021-11-19
## Added  
- Ported StatusLine

#### 2.16.0 (2021-11-19
## Added  
- Documented Vendor/Server.cpp
* [RSi-12]

#### 2.15.0 (2021-11-18)
## Added  
- Added ColorBar 
* [RSi-9B]

#### 2.14.0 (2021-11-18)
## Added  
- Added maxcount 
* [RSi-9]

#### 2.13.1 (2021-11-18)
## Added  
- StatusBarInterface
* [RSi-9]

#### 2.13.0 (2021-11-18)
## Added  
- StatusBarInterface
* [RSi-9]

#### 2.12.0 (2021-11-16)
## Added  
- StatusLineInterface
* [RSi-8]

#### 2.11.0 (2021-11-16)
## Added  
- ServiceTypeCompilerVendor
* [RSi-7]

#### 2.10.0 (2021-11-16)
- Using extras 5.2.0

#### 2.9.0 (2021-11-15)
- Using extras 5.1.1

#### 2.8.0 (2021-11-15)
- Added shared executables parameter

#### 2.7.0 (2021-11-15)
- Added ng-monitor

#### 2.6.0 (2021-11-15)
- Refactored unused code 

#### 2.5.0 (2021-11-14)
- Removed needess output from parcel pack/unpack 

#### 2.4.0 (2021-11-14)
- MAKE_EXPARX_RSI_LIBRARY_TOOLS support

#### 2.3.0 (2021-11-14)
- MAKE_EXPARX_RSI_LIBRARY_ONLY support

#### 2.2.0 (2021-11-14)
- Operational Prototype

#### 2.0.0 (2021-11-10)
- New branch based on RSI-6B
- Updated README.md 

#### 1.2.0 (2021-11-10)
- using perriera/extras v5.0.9
- Updated README.md 

#### 1.1.4 (2021-11-10)
- using perriera/extras v5.0.8
- Updated README.md 

#### 1.1.3 (2021-11-10)
- using perriera/extras v5.0.4
- RSI-4

#### 1.1.2 (2021-11-10)
- Changed message
- RSI-4

#### 1.1.1 (2021-11-10)
- Trimmed code/updated docs
- RSI-4

#### 1.0.1 (2021-11-09)
- Added bin2hex
- Now using extras 5.0.1
- RSI-4

#### 1.0.0 (2021-11-09)
- Changed namespace from exparx to extras, (aka. extras::rsi)
- RSI-3

#### 0.3.1 (2021-11-08)
- Updated changelog
- RSI-2

#### 0.3.0 (2021-11-08)
- Ported over most of the necessary code
- RSI-2

#### 0.2.0 (2021-11-08)
- Now using perriera/extras v4.19.0

#### 0.1.0 (2021-11-08)
- rsi source code
- SHARED library support
- (perriera) extras library support, (3.11.0)
- CPM.cmake support
  * [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake/blob/master/LICENSE) 
  * This allows us to include other Github packages with the ability
    to add package OPTIONS
- FakeIt Mock Library support
  * [FakeIt](https://github.com/eranpeer/FakeIt) 
  * This gives us the ability to mock C++ interfaces, (before implementation)
- Catch2 support
  * [Catch2](https://github.com/catchorg/Catch2)
  * This gives us the ability to test C++ classes, (during implementation)
### Changed
- CMakeLists.txt
  * [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter/blob/master/LICENSE) 
- spdlog is now used as a shared library, (libspdlog.so)
- cpr is now used as a shared library, (libcpr.so)
- placed all source into /src
- placed all headers into /include/rsi
- Fetch_Content support
- changelog.md
- Project VERSION inside CMakeLists.txt & changelog.md
- Adopted new changelog format.
- sudo make install parameters
- shared library support
- sudo checkinstall support
- GoF: Abstract design pattern support
- Debian package support
- extra/interfaces.hpp support
- Unit test casses support, (Catch2)
- Mock framework support, (FakeIt)

### Changed
- CMakeLists.txt revamped & streamlined
- README.md revamped & streamlined
- Added documentation on code
- cxx_std_17 on all targets
- std::filesystem on all targets

### Maintained
- @brief style formatting
- Doxygen support 

### Removed
- Conan package manager deprecated

[Unreleased]: https://github.com/perriera/rsi/compare/v3.0.1...HEAD
[3.0.1]: https://github.com/perriera/rsi/compare/v3.0.0...v3.0.1
[3.0.0]: https://github.com/perriera/rsi/compare/v2.17.0...v3.0.0
[2.17.0]: https://github.com/perriera/rsi/compare/v2.16.0...v2.17.0
[2.16.0]: https://github.com/perriera/rsi/compare/v2.15.0...v2.16.0
[2.15.0]: https://github.com/perriera/rsi/compare/v2.14.0...v2.15.0
[2.14.0]: https://github.com/perriera/rsi/compare/v2.13.0...v2.14.0
[2.13.1]: https://github.com/perriera/rsi/compare/v2.13.0...v2.13.1
[2.13.0]: https://github.com/perriera/rsi/compare/v2.12.0...v2.13.0
[2.12.0]: https://github.com/perriera/rsi/compare/v2.11.0...v2.12.0
[2.11.0]: https://github.com/perriera/rsi/compare/v2.10.0...v2.11.0
[2.10.0]: https://github.com/perriera/rsi/compare/v2.9.0...v2.10.0
[2.9.0]: https://github.com/perriera/rsi/compare/v2.8.0...v2.9.0
[2.8.0]: https://github.com/perriera/rsi/compare/v2.7.0...v2.8.0
[2.7.0]: https://github.com/perriera/rsi/compare/v2.6.0...v2.7.0
[2.6.0]: https://github.com/perriera/rsi/compare/v2.5.0...v2.6.0
[2.5.0]: https://github.com/perriera/rsi/compare/v2.4.0...v2.5.0
[2.4.0]: https://github.com/perriera/rsi/compare/v2.3.0...v2.4.0
[2.3.0]: https://github.com/perriera/rsi/compare/v2.2.0...v2.3.0
[2.2.0]: https://github.com/perriera/rsi/compare/v2.1.0...v2.2.0
[2.1.0]: https://github.com/perriera/rsi/compare/v2.0.0...v2.1.0
[2.0.0]: https://github.com/perriera/rsi/compare/v1.2.0...v2.0.0
[1.2.0]: https://github.com/perriera/rsi/compare/v1.1.4...v1.2.0
[1.1.4]: https://github.com/perriera/rsi/compare/v1.1.3...v1.1.4
[1.1.3]: https://github.com/perriera/rsi/compare/v1.1.2...v1.1.3
[1.1.2]: https://github.com/perriera/rsi/compare/v1.1.1...v1.1.2
[1.1.1]: https://github.com/perriera/rsi/compare/v1.0.1...v1.1.1
[1.0.1]: https://github.com/perriera/rsi/compare/v1.0.0...v1.0.1
[1.0.0]: https://github.com/perriera/rsi/compare/v0.3.1...v1.0.0
[0.3.1]: https://github.com/perriera/rsi/compare/v0.3.0...v0.3.1
[0.3.0]: https://github.com/perriera/rsi/compare/v0.2.0...v0.3.0
[0.2.0]: https://github.com/perriera/rsi/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/perriera/rsi/releases/tag/v0.1.0
