file(GLOB_RECURSE SOURCE_FILES "*.cpp")

find_package(Boost 1.54.0 REQUIRED)
set(BOOST_ROOT /usr/local)
include_directories(${Boost_INCLUDE_DIRS})
#find_package(Threads REQUIRED)

include_directories(".")
ADD_LIBRARY(scene_interface ${SOURCE_FILES})
SET_TARGET_PROPERTIES(scene_interface PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
#SET_TARGET_PROPERTIES(scene_interface PROPERTIES LINK_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_system -lpthread -lboost_thread -lrt")
TARGET_LINK_LIBRARIES(scene_interface ${Boost_LIBRARIES})
#TARGET_LINK_LIBRARIES(scene_interface ${CMAKE_THREAD_LIBS_INIT})
