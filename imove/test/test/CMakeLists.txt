file(GLOB_RECURSE TEST_FILES "*.cpp")

add_executable(runMyTests ${TEST_FILES})

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

target_link_libraries(runMyTests gtest gtest_main gmock gmock_main)
target_link_libraries(runMyTests imove)