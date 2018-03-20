cmake_minimum_required(VERSION 3.9)

aux_source_directory(. DIR)
add_library(LibSecurity ${DIR})

target_link_libraries(
        LibSecurity

        # Cryptopp
        cryptopp
)
