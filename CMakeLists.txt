cmake_minimum_required(VERSION 3.10)
project(ROOT)
enable_testing()
include_directories(src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(test/gtestDir)
add_subdirectory(src)
add_subdirectory(test)
