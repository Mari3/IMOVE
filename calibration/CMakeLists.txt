file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "../scene_interface/src/*.cpp")

ADD_EXECUTABLE(calibration src/main.cpp ${SOURCE_FILES} ../imove_peopleextractor/src/OpenCVUtil.cpp ../imove_peopleextractor/src/OpenCVWindow.cpp ../imove_peopleextractor/src/Calibration/Calibration.cpp)
SET_TARGET_PROPERTIES(calibration PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

TARGET_LINK_LIBRARIES(calibration ${OpenCV_LIBS})
