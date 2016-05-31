file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

find_package(Boost 1.54.0)
include_directories(${Boost_INCLUDE_DIRS})

ADD_LIBRARY(scene-interface ${SOURCE_FILES})
SET_TARGET_PROPERTIES(scene-interface PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
