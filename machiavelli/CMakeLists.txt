cmake_minimum_required(VERSION 3.9)
project(machiavelli)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp)
add_executable(machiavelli ${SOURCES})

target_include_directories(machiavelli
        PUBLIC include/)

target_link_libraries(machiavelli
        PUBLIC networking)

add_custom_command(TARGET machiavelli POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:machiavelli>)