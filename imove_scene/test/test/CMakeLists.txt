project(tests)

file(GLOB_RECURSE TEST_FILES "*.cpp")

file(GLOB_RECURSE IMOVE_SOURCES "../scene_interface/src/*.h" "../../src/Util/*.h"
        "../../src/Util/*.cpp" "../../src/Scene/*.h" "../../src/Scene/*.cpp" "../../../../utill/src/*.cpp")

add_executable(runMyTests ${TEST_FILES} ${IMOVE_SOURCES})

include_directories(../lib/fakeit)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

target_link_libraries(runMyTests gtest gtest_main)
target_link_libraries(runMyTests imove_scene)
