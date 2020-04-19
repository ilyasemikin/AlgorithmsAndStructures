cmake_minimum_required(VERSION 3.10)

project(tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

include_directories(
	${includes}
	${GTEST_INCLUDE_DIRS}	
)

add_executable(
	test_task
	tests.cpp
	../src/strings_split.cpp
)
target_link_libraries(
	test_task
	${GTEST_LIBRARIES}
)

enable_testing()
add_test(test_task "./test_task")
