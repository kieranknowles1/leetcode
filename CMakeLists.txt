project(leetcode)
cmake_minimum_required(VERSION 4.1.0)

file(STRINGS sources.txt SOURCES)

foreach(SRC ${SOURCES})
    get_filename_component(filename ${SRC} NAME_WE)
    add_executable(${filename} ${SRC})
endforeach()
