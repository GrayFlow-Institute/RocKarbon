cmake_minimum_required(VERSION 3.9)
project(Rockarbon_Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# GTest Include
add_subdirectory(./lib/gtest)
include_directories(
        ./lib/gtest/googletest/include
        ./lib/gtest/googlemock/include
)


aux_source_directory(. DIR)

add_executable(
        Rockarbon_Test

        # Main Test
        ${DIR}
)

target_link_libraries(
        Rockarbon_Test

        # GTest
        gtest
        gtest_main

        # Test Modules
        LibLogger
        LibNetwork
        LibSecurity
        LibStorage
        LibSystem
        #LibTools
)