cmake_minimum_required(VERSION 3.9)

aux_source_directory(. DIR)
add_library(LibSystem ${DIR})

include_directories(
        /usr/include
        ../../interface
)

target_link_libraries(
        LibSystem

        # 依赖于 log 和 stroage ，因为有工厂嘛
        LibLogger
        LibStorage
)
