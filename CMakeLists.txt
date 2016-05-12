cmake_minimum_required(VERSION 3.2.2)
project(imove)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules/")

find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
find_package(OpenCV REQUIRED HINTS ${OpenCV_DIR})
include_directories( ${OpenCV_INCLUDE_DIRS} )

file(GLOB_RECURSE SOURCE_FILES "src/*.h" "src/*.cpp")

#set(SOURCE_FILES src/main.cpp src/scene/Scene.cpp src/scene/Scene.h)
add_executable(imove ${SOURCE_FILES} src/scene/LightTrail/LightTrail.cpp src/scene/LightTrail/LightTrail.h)
target_link_libraries(imove ${SFML_LIBRARIES})
target_link_libraries(imove ${OPENCV_LIBRARIES})
