cmake_minimum_required(VERSION 3.10)
project(${PROJECT_NAME}_OS)

set(LIBRARY ${CMAKE_PROJECT_NAME}_lib)

enable_testing()

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.h *.hpp *.c *.cpp)
message(${SOURCES})

set(CMAKE_CXX_FLAGS -pthread)

set(SOURCES ${SOURCES})

add_library(${LIBRARY} STATIC ${SOURCES})

target_link_libraries(${LIBRARY} pthread)