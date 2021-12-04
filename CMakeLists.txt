#
# NOTE: determine required cmake here (use 'pip install cmake')
#
cmake_minimum_required(VERSION 3.21)

#
# NOTE: Include our own cmake scripts, and the CPM package manager
#
include(cmake/CPM.cmake)
include(cmake/print.cmake)
include(cmake/utils.cmake)
extras_rsi_get_version()
project(
  extras_rsi
  VERSION ${EXTRAS_RSI_VERSION}
  LANGUAGES CXX
)

#
# NOTE: Set our source and include directory variables for use through the build
#
set(SOURCES "${PROJECT_SOURCE_DIR}/src")
set(INCLUDES "${PROJECT_SOURCE_DIR}/include")

#
# NOTE: Prevent in source builds (can't build in src/ or in project root)
#
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR OR PROJECT_BINARY_DIR STREQUAL SOURCES)
  print(
    FATAL_ERROR
    "In source builds are not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()
print(STATUS "Building ${PROJECT_NAME}-${PROJECT_VERSION}")

#
# NOTE: bring in standard cmake includes
#
include(CMakeDependentOption)
include(GNUInstallDirs)
include(CheckIPOSupported)

#
# NOTE: Export compile_commands.json file to support clang tooling
#
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# NOTE: Set C/C++ parameters for all targets in this CMakeLists.txt
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic --std=c++17 -fPIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -fPIC")

# add additional project options
message(STATUS "MAKE_EXPARX_RSI_LIBRARY_ONLY is ${MAKE_EXPARX_RSI_LIBRARY_ONLY}")
if(MAKE_EXPARX_RSI_LIBRARY_ONLY)
  option(BUILD_TESTS "Build tests" OFF)
  option(DEBUG "Debug Build" OFF)
  set(RSI_TESTS OFF)
  message(STATUS "BUILD_TESTS is ${BUILD_TESTS}")
  message(STATUS "DEBUG is ${DEBUG}")
else()
  option(BUILD_TESTS "Build tests" ON)
  option(DEBUG "Debug Build" ON)
  message(STATUS "BUILD_TESTS is ${BUILD_TESTS}")
  message(STATUS "DEBUG is ${DEBUG}")

  #
  # NOTE: add additional project options
  #
  option(RSI_PRODUCTION "Production build" OFF)

  #
  # NOTE: Build defaults to production, cmake -DRSI_PRODUCTION=OFF will build debug with tests
  #
  if(NOT RSI_PRODUCTION)
    print(STATUS "Building ${PROJECT_NAME}-${PROJECT_VERSION} [DEBUG]")
    set(CMAKE_BUILD_TYPE Debug)
    set(RSI_TESTS ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
  else()
    print(STATUS "Building ${PROJECT_NAME}-${PROJECT_VERSION} [RELEASE]")
    set(RSI_TESTS OFF)
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
  endif()
endif()

#
# NOTE: Output build param information
#
print(STATUS "edit your ~/.bashrc and set")
print(STATUS "export LD_LIBRARY_PATH=/usr/local/lib")
print(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
print(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")

#
# NOTE: " Include 3rd party libraries, Perry and I maintain an open-source extras C++ library, which
# is used extensively in extras_rsi, it comes bundled with spdlog, cpr, and nlohmann json. extras has
# project options that allow us to control how other libraries it includes are built. for example we
# can tell extras to build spdlog as a static library (for faster compile times) by settings
# MAKE_SPDLOG_SHARED OFF " -- Matt Williams, October 2021 
#
CPMAddPackage(
  NAME extras_arc
  GITHUB_REPOSITORY perriera/extras_arc
  VERSION 2.0.0
  OPTIONS "MAKE_SPDLOG_SHARED OFF"
  OPTIONS "MAKE_EXTRAS_LIBRARY_ONLY ON"
  OPTIONS "MAKE_EXTRAS_ARC_LIBRARY_ONLY ON"
)
if(extras_arc_ADDED)
  #
  # NOTE:  enable c++11 to avoid compilation errors, and force spdlog into release build
  #
  print(STATUS "Configuring extras_arc build properties")
  set_target_properties(extras_arc PROPERTIES CMAKE_BUILD_TYPE Release)
else()
  print(WARNING "extras_arc was not configured properly")
endif()

#
# HACK: glob src files and header files
#
file(GLOB_RECURSE RSI_HEADERS CONFIGURE_DEPENDS "${INCLUDES}/${PROJECT_NAME}/*.hpp")
file(GLOB_RECURSE RSI_SOURCE CONFIGURE_DEPENDS "${SOURCES}/*.cpp")

#
# NOTE: declare libraries here all source should be placed into a single library, (whether they be
# shared or static)
#
add_library(${PROJECT_NAME} SHARED ${RSI_HEADERS} ${RSI_SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs extras extras_arc)

#
# NOTE: declare unit test cases here all source should have adequate test cases whether they be mock
# or unit tests, (or both)
#
if (NOT MAKE_EXPARX_RSI_LIBRARY_ONLY)
  if(RSI_TESTS)
    print(STATUS "Building tests")
    file(GLOB_RECURSE RSI_TESTS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")
    set(TEST_EXEC "run-unittests-${PROJECT_NAME}")
    add_executable(${TEST_EXEC} ${RSI_TESTS})
    target_include_directories(${TEST_EXEC} PUBLIC ${INCLUDES})
    target_link_libraries(${TEST_EXEC} PRIVATE ${PROJECT_NAME} stdc++fs extras extras_arc)
  endif()
endif()

#
# TODO: declare example client usage application code here, this is where regression tests should
# ultimately be written. as well, this make file uses a GLOB_RECURSE macro which automatically 
# includes ALL headers and sources under include/ and src/. So, to keep two or more main() 
# declarations seperate, we place any sources that have a main() in the instances/ folder
#

#
# socketpool_client/server
#
if(NOT MAKE_EXPARX_RSI_LIBRARY_ONLY OR MAKE_EXPARX_RSI_LIBRARY_TOOLS)
add_executable(socketpool_client instances/socketpool_client.cpp) 
target_include_directories(socketpool_client PUBLIC ${INCLUDES})
target_link_libraries(socketpool_client PRIVATE ${PROJECT_NAME} stdc++fs extras extras_arc)

add_executable(socketpool_server instances/socketpool_server.cpp) 
target_include_directories(socketpool_server PUBLIC ${INCLUDES})
target_link_libraries(socketpool_server PRIVATE ${PROJECT_NAME} stdc++fs extras extras_arc)
endif()

#
# uploader_client/server
#
if(NOT MAKE_EXPARX_RSI_LIBRARY_ONLY OR MAKE_EXPARX_RSI_LIBRARY_TOOLS)
add_executable(uploader_client instances/uploader_client.cpp) 
target_include_directories(uploader_client PUBLIC ${INCLUDES})
target_link_libraries(uploader_client PRIVATE ${PROJECT_NAME} stdc++fs extras extras_arc)

add_executable(uploader_server instances/uploader_server.cpp) 
target_include_directories(uploader_server PUBLIC ${INCLUDES})
target_link_libraries(uploader_server PRIVATE ${PROJECT_NAME} stdc++fs extras extras_arc)
endif()

#
# downloader_client/server
#
if(NOT MAKE_EXPARX_RSI_LIBRARY_ONLY OR MAKE_EXPARX_RSI_LIBRARY_TOOLS)
add_executable(downloader_client instances/downloader_client.cpp) 
target_include_directories(downloader_client PUBLIC ${INCLUDES})
target_link_libraries(downloader_client PRIVATE ${PROJECT_NAME} stdc++fs extras extras_arc)

add_executable(downloader_server instances/downloader_server.cpp) 
target_include_directories(downloader_server PUBLIC ${INCLUDES})
target_link_libraries(downloader_server PRIVATE ${PROJECT_NAME} stdc++fs extras extras_arc)
endif()

#
# vendor_client/server 
#
if(NOT MAKE_EXPARX_RSI_LIBRARY_ONLY OR MAKE_EXPARX_RSI_LIBRARY_TOOLS)
add_executable(vendor_client instances/vendor_client.cpp) 
target_include_directories(vendor_client PUBLIC ${INCLUDES})
target_link_libraries(vendor_client PRIVATE ${PROJECT_NAME} stdc++fs extras extras_arc)

add_executable(vendor_server instances/vendor_server.cpp) 
target_include_directories(vendor_server PUBLIC ${INCLUDES})
target_link_libraries(vendor_server PRIVATE ${PROJECT_NAME} stdc++fs extras extras_arc)
endif()

#
# NOTE: Install all shared libraries & executables
#
install(TARGETS 
  socketpool_client socketpool_server
  uploader_client uploader_server 
  vendor_client vendor_server 
  downloader_client downloader_server 
  ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

#
# NOTE: if the compiler supports iter-procedural optimization, turn it on
#
check_ipo_supported(RESULT result OUTPUT output)
if(result)
  print(STATUS "Building ${PROJECT_NAME} with Interprocedural Optimization")
  set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
  print(WARNING "IPO is not supported: ${output}")
endif()

set_target_properties(
  ${PROJECT_NAME} PROPERTIES VERSION ${${PROJECT_NAME}_VERSION} SOVERSION
                                                                ${${PROJECT_NAME}_VERSION_MAJOR}
)
