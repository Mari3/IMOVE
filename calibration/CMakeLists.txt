ADD_EXECUTABLE(calibration src/main.cpp)
TARGET_LINK_LIBRARIES(calibration ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(calibration util)