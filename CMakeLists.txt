cmake_minimum_required(VERSION 4.1.0)
project(leetcode)

# Advent of code often relies on larger values than can fit in a u32. Check
# for overflows caused by this.
add_compile_options(-fsanitize=integer)
add_link_options(-fsanitize=integer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
      ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

file(STRINGS sources.txt SOURCES)

foreach(SRC ${SOURCES})
    get_filename_component(filename ${SRC} NAME_WE)
    add_executable(${filename} ${SRC})
endforeach()
