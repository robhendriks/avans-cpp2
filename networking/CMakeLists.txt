cmake_minimum_required(VERSION 3.9)
project(networking)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(networking STATIC ${SOURCES})

target_include_directories(networking
        PUBLIC include)