add_executable(runTests test1.cpp)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

target_link_libraries(runTests gtest gtest_main)
target_link_libraries(runTests imove)