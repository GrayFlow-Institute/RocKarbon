cmake_minimum_required(VERSION 3.9)

include_directories(
        ../interfase
)

aux_source_directory(. DIR)
add_library(LibStorage ${DIR})
