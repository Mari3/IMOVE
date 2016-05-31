find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})
find_package(OpenCV REQUIRED HINTS ${OpenCV_DIR})
include_directories( ${OpenCV_INCLUDE_DIRS} )


file(GLOB_RECURSE SOURCE_FILES "*.cpp")
ADD_EXECUTABLE(imove-peopleextractor ${SOURCE_FILES})
SET_TARGET_PROPERTIES(imove-peopleextractor PROPERTIES ENABLE_EXPORTS true)
SET_TARGET_PROPERTIES(imove-peopleextractor PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

TARGET_LINK_LIBRARIES(imove-peopleextractor ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(imove-peopleextractor ${SFML_LIBRARIES})
