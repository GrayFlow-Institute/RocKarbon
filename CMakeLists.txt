cmake_minimum_required(VERSION 3.9)
project(Rockarbon)

set(CMAKE_CXX_STANDARD 11)
#SET(GCC_COVERAGE_LINK_FLAGS "-lrt -lpthread")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

add_executable(Rockarbon main.cpp base/Daemon.cpp base/Daemon.h base/Env.cpp base/Env.h)