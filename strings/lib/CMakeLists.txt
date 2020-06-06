cmake_minimum_required(VERSION 3.10)

project(
    strings_processing 
    VERSION 1.0.0 
    DESCRIPTION "C++ library for string processing"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(
    HEADERS
    include/prefix.hpp
    include/string_find_substr.hpp
    include/string_split.hpp
)

set(
    SOURCES
    src/prefix.cpp
    src/string_kmp.cpp
    src/string_bmh.cpp
    src/string_split.cpp
)

add_library(strings_processing STATIC
    ${SOURCES}
)

target_include_directories(strings_processing PUBLIC include)