cmake_minimum_required(VERSION 3.9)
project(Rockarbon)

set(CMAKE_CXX_STANDARD 11)
#SET(GCC_COVERAGE_LINK_FLAGS "-lrt -lpthread")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(
        Rockarbon
        src/main.cpp
        src/base/system/Daemon.cpp
        src/base/system/Daemon.h
        src/base/system/Env.cpp
        src/base/system/Env.h
        src/base/security/AESGuard.cpp
        src/base/security/AESGuard.h
        src/base/security/RSAGuard.cpp
        src/base/security/RSAGuard.h
        src/base/security/HashGuard.cpp
        src/base/security/HashGuard.h
        src/base/interface/StorageBase.h
        src/base/storage/StorageFactory.cpp
        src/base/storage/StorageFactory.h
        src/base/network/DiscService.cpp
        src/base/network/DiscService.h
)