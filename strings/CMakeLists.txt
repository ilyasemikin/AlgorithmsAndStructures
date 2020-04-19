cmake_minimum_required(VERSION 3.10)

set(pr_name task)
set(
	includes 
	include
)
set(
	sources
	src/main.cpp
	src/strings_split.cpp
)

project(${pr_name} LANGUAGES CXX C)

include_directories(
	${includes}
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
	${pr_name}
	${sources}
)
target_link_libraries(${pr_name} PRIVATE)
target_compile_options(
	${pr_name} PRIVATE 
	-Wall -Wextra -pedantic -Werror
)

enable_testing()
add_subdirectory(tests)
