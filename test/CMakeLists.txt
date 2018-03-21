cmake_minimum_required(VERSION 3.9)
project(Rockarbon_Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# GTest Include
add_subdirectory(./lib/gtest)
include_directories(
        ./lib/gtest/googletest/include
        ./lib/gtest/googlemock/include
        /usr/local/include/cryptopp
)

aux_source_directory(. DIR)
aux_source_directory(logger LOGGER)
aux_source_directory(security SECURTIY)
aux_source_directory(storage STORAGE)
aux_source_directory(network NETWORK)
aux_source_directory(system SYSTEM)
aux_source_directory(tools TOOLS)

add_executable(
        Rockarbon_Test
        # Main Test
        ${DIR}

        # Modules Test
        ${LOGGER}
        ${SECURTIY}
        ${STORAGE}
        ${SYSTEM}
        ${NETWORK}
        ${TOOLS}
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
        LibTools
)