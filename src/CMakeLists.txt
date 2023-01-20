cmake_minimum_required(VERSION 3.14)
project(${PROJECT_NAME}_OS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LIBRARY ${CMAKE_PROJECT_NAME})

enable_testing()

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.h *.hpp *.c *.cpp)
message(${SOURCES})

set(CMAKE_CXX_FLAGS -pthread)

set(SOURCES ${SOURCES})

add_library(${LIBRARY} STATIC ${SOURCES})

target_link_libraries(${LIBRARY} pthread)

add_executable(main evSysMain.cpp)

target_link_libraries(main ${LIBRARY})