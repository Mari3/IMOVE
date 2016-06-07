file(GLOB_RECURSE SOURCE_FILES "*.cpp")

find_package(Boost 1.54.0 REQUIRED)
set(BOOST_ROOT /usr/local)
include_directories(${Boost_INCLUDE_DIRS})
#find_package(Threads REQUIRED)

include_directories(".")
ADD_LIBRARY(peopleextractor_interface_sma ${SOURCE_FILES})
SET_TARGET_PROPERTIES(peopleextractor_interface_sma PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
#SET_TARGET_PROPERTIES(peopleextractor_interface_sma PROPERTIES LINK_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_system -lpthread -lboost_thread -lrt")
TARGET_LINK_LIBRARIES(peopleextractor_interface_sma ${Boost_LIBRARIES})
#TARGET_LINK_LIBRARIES(peopleextractor_interface_sma ${CMAKE_THREAD_LIBS_INIT})
