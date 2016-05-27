file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

ADD_EXECUTABLE(Calibration src/main.cpp ${SOURCE_FILES} ../imove/src/OpenCVUtil.cpp ../imove/src/OpenCVWindow.cpp ../imove/src/Calibration/Calibration.cpp ../imove/src/Interface/Person.cpp ../imove/src/Util/Vector2.cpp)

TARGET_LINK_LIBRARIES(Calibration ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(Calibration Util)
