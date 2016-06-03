file(GLOB_RECURSE SOURCE_FILES "*.cpp")

include_directories(".")
ADD_LIBRARY(scene_interface ${SOURCE_FILES})
SET_TARGET_PROPERTIES(scene_interface PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
