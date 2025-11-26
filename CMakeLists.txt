project(leetcode)
cmake_minimum_required(VERSION 4.1.0)

set(SOURCES
    src/21-parentheses.cpp
)

foreach(SRC ${SOURCES})
    get_filename_component(filename ${SRC} NAME_WE)
    add_executable(${filename} ${SRC})
endforeach()
