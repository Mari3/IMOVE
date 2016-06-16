project(scene-controllers)

find_package(SFML 2.3.0 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
find_package(OpenCV REQUIRED HINTS ${OpenCV_DIR})
include_directories( ${OpenCV_INCLUDE_DIRS} )


file(GLOB_RECURSE IMOVE_SOURCES "../../../scene_interface/src/*.cpp" "../../src/Util/*.h"
        "../../src/Util/*.cpp" "../../src/Scene/*.h" "../../src/Scene/*.cpp" "../../../util/src/*.cpp")
ADD_EXECUTABLE(scene-controllers ${IMOVE_SOURCES} main.cpp )
SET_TARGET_PROPERTIES(scene-controllers PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

TARGET_LINK_LIBRARIES(scene-controllers ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(scene-controllers ${SFML_LIBRARIES})
