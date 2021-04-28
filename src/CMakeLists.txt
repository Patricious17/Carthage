cmake_minimum_required(VERSION 3.10)
project(Planner)

set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS -pthread)

enable_testing()

include_directories(include ${gtest_SOURCE_DIR}/include/gtest)

#add_library(Map2d map2d.cpp include/map2d.hpp)
add_library(eventSystem eventSystem.cpp include/eventSystem.hpp)
target_link_libraries(eventSystem gtest gtest_main)
add_executable(Planner plannerMain.cpp include/plannerMain.hpp include/basicTypes.hpp include/eventSystem.hpp eventSystem.cpp)

target_link_libraries(Planner eventSystem pthread)
