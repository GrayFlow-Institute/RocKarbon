cmake_minimum_required(VERSION 3.9)
project(Rockarbon_Run)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
        /usr/include/cryptopp
        /usr/local/include/cryptopp
)

# LibLogger
add_subdirectory(base/log)

# LibNetwork
add_subdirectory(base/network)

# LibSecurity
add_subdirectory(base/security)

# LibStorage
add_subdirectory(base/storage)

# LibSystem
add_subdirectory(base/system)

# LibTools
add_subdirectory(base/tools)

# Rockarbon
aux_source_directory(. DIR_SRCS)
add_executable(Rockarbon_Run ${DIR_SRCS})

target_link_libraries(
        Rockarbon_Run

        # Boost::ASIO
        pthread
        boost_system
        boost_filesystem

        # Cryptopp
        cryptopp

        # My Modules
        LibLogger
        LibNetwork
        LibSecurity
        LibStorage
        LibSystem
        LibTools
)
