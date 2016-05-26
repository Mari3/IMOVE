ADD_EXECUTABLE(calibration src/main.cpp ../imove/src/calibration/Calibration.cpp ../imove/src/interface/Person.cpp ../imove/src/util/Vector2.cpp)
TARGET_LINK_LIBRARIES(calibration ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(calibration util)
