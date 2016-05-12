cmake_minimum_required(VERSION 3.2.2)
project(imgproc)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(imgproc main.cpp PeopleDetector.h PeopleDetector.cpp Person.h Person.cpp Vector2.h Vector2.cpp)
target_link_libraries(imgproc ${OpenCV_LIBS})
