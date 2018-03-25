cmake_minimum_required(VERSION 3.9)

aux_source_directory(. DIR)
add_library(LibNetwork ${DIR})

include_directories(
        /usr/include
        ../../interface
)

target_link_libraries(
        LibNetwork

        # 依赖自己的库
        LibSecurity
        LibStorage
        LibTools

        # Boost::ASIO
        pthread
        boost_thread
        boost_system
        boost_filesystem
        boost_regex
        boost_date_time
)