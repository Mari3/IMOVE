file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "../scene_interface/src/*.cpp" "../util/src/*.cpp")

ADD_EXECUTABLE(calibration src/main.cpp ${SOURCE_FILES})
SET_TARGET_PROPERTIES(calibration PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

TARGET_LINK_LIBRARIES(calibration ${OpenCV_LIBS})
