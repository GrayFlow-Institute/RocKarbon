cmake_minimum_required(VERSION 3.9)
project(Rockarbon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# GTest Include
add_subdirectory(./lib/gtest)
include_directories(
        ./lib/gtest/googletest/include
        ./lib/gtest/googlemock/include
)


# LibLogger
add_subdirectory(./src/base/log)

# LibNetwork
add_subdirectory(./src/base/network)

# LibSecurity
add_subdirectory(./src/base/security)

# LibStorage
add_subdirectory(./src/base/storage)

# LibSystem
add_subdirectory(./src/base/system)

# LibTools
#add_subdirectory(./src/base/tools)


# Rockarbon
aux_source_directory(./src DIR_SRCS)
add_executable(Rockarbon ${DIR_SRCS})

target_link_libraries(
        Rockarbon

        # GTest
        gtest
        gtest_main

        # Boost::ASIO
        pthread
        boost_system

        # My Modules
        LibLogger
        LibNetwork
        LibSecurity
        LibStorage
        LibSystem
#        LibTools
)
