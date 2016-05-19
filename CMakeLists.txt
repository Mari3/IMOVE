cmake_minimum_required(VERSION 3.2.2)
 
PROJECT(application)
 
FIND_PACKAGE(OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
if(MSVC)
  # Force to always compile with W4
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
	string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()
 
ADD_EXECUTABLE(calibration calibration/src/main.cpp scene/src/calibration/Calibration.cpp)
ADD_EXECUTABLE(scene scene/src/main.cpp scene/src/calibration/Calibration.cpp scene/src/image_processing/PeopleDetector.h scene/src/image_processing/PeopleDetector.cpp scene/src/image_processing/Person.h scene/src/image_processing/Person.cpp scene/src/image_processing/Vector2.h scene/src/image_processing/Vector2.cpp)
TARGET_LINK_LIBRARIES(calibration ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(scene ${OpenCV_LIBS})
