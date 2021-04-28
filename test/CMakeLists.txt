cmake_minimum_required(VERSION 3.10)
project(Tests)

################################
# GTest
################################
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/src/include ${CMAKE_SOURCE_DIR}/src ${CMAKE_PROJECT_DIR}/src)

################################
# Unit Tests
################################
# Add test cpp file

add_executable( runUnitTests src/test.cpp)

add_library(evSys ${CMAKE_SOURCE_DIR}/src/eventSystem.cpp ${CMAKE_SOURCE_DIR}/src/include/eventSystem.hpp)
# Link test executable against gtest & gtest_main

target_link_libraries(runUnitTests evSys gtest gtest_main)
add_test( runUnitTests runUnitTests )
