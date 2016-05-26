
add_subdirectory(util)

find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
find_package(OpenCV REQUIRED HINTS ${OpenCV_DIR})
include_directories( ${OpenCV_INCLUDE_DIRS} )


file(GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp")
ADD_EXECUTABLE(imove ${SOURCE_FILES})
SET_TARGET_PROPERTIES(imove PROPERTIES ENABLE_EXPORTS true)

TARGET_LINK_LIBRARIES(imove ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(imove ${SFML_LIBRARIES})
