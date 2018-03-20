cmake_minimum_required(VERSION 3.9)

aux_source_directory(. DIR)
add_library(LibSystem ${DIR})

target_link_libraries(
        LibSystem

        # 依赖于 log
        LibLogger
)
