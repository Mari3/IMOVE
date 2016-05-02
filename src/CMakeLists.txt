cmake_minimum_required(VERSION 2.6)
 
PROJECT(application)
 
FIND_PACKAGE(OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
 
ADD_EXECUTABLE(application CheckerboardCalibration.cxx)
TARGET_LINK_LIBRARIES(application ${OpenCV_LIBS})
