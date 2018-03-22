cmake_minimum_required(VERSION 3.9)

aux_source_directory(. DIR)
add_library(LibNetwork ${DIR})

include_directories(
        /usr/include
        ../../interface
        ../../base/security
)

target_link_libraries(
        LibNetwork

        # 依赖自己的库
        LibSecurity
        LibStorage

        # Boost::ASIO
        pthread
        boost_system
        boost_filesystem
)