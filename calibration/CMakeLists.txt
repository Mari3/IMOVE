file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

ADD_EXECUTABLE(calibration src/main.cpp ${SOURCE_FILES} ../imove-peopleextractor/src/OpenCVUtil.cpp ../imove-peopleextractor/src/OpenCVWindow.cpp ../imove-peopleextractor/src/Calibration/Calibration.cpp ../imove-peopleextractor/src/Interface/Person.cpp ../imove-peopleextractor/src/Util/Vector2.cpp)
SET_TARGET_PROPERTIES(calibration PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

TARGET_LINK_LIBRARIES(calibration ${OpenCV_LIBS})
