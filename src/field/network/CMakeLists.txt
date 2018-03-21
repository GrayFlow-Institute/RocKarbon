cmake_minimum_required(VERSION 3.9)

aux_source_directory(. DIR)
add_library(LibNetwork ${DIR})
include_directories(
        /usr/include
        ../interfase
)

target_link_libraries(
        LibNetwork

        # Boost::ASIO
        pthread
        boost_system
        boost_filesystem
)