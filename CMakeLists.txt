cmake_minimum_required(VERSION 3.5)
project(opencvtest)

find_package(OpenCV HINTS ${OPENCV_DIR})
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(opencvtest ${SOURCE_FILES})
target_link_libraries( opencvtest ${OpenCV_LIBS} )