project(scene-integration)

find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
find_package(OpenCV REQUIRED HINTS ${OpenCV_DIR})
include_directories( ${OpenCV_INCLUDE_DIRS} )


file(GLOB_RECURSE IMOVE_SOURCES "../../../src/interface/*.h" "../../../src/interface/*.cpp" "../../../src/util/*.h"
        "../../../src/util/*.cpp" "../../../src/scene/*.h" "../../../src/scene/*.cpp")
ADD_EXECUTABLE(scene-integration ${IMOVE_SOURCES} main.cpp )

TARGET_LINK_LIBRARIES(scene-integration ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(scene-integration ${SFML_LIBRARIES})
#TARGET_LINK_LIBRARIES(scene-integration imove)