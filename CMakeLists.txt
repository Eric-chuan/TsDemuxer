cmake_minimum_required(VERSION 3.5)
project(ts_demuxer)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Os -Wall -pedantic")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# inlcude path
include_directories(include)


add_executable(ts_demuxer ${SOURCES})
#if there is subdirectories
#target_link_libraries(ts_demuxer subdirectories)
