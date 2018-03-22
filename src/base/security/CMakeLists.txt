cmake_minimum_required(VERSION 3.9)

include_directories(
        ../interfase
)

aux_source_directory(. DIR)
add_library(LibSecurity ${DIR})


target_link_libraries(
        LibSecurity

        # Cryptopp
        cryptopp
)
