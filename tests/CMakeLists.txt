cmake_minimum_required(VERSION 3.14)
project(test_${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

add_executable(test test.cpp)
target_link_libraries(test gtest_main)
add_test(unitTests test.cpp)
target_link_libraries(test CARTHAGE)