# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#tests for lab2
include_directories(../lab2/lib)
add_executable(Google_Tests_run_lab2 ../lab2/test/test.cpp)
#add_library(lib_deltoid ../lab2/lib/deltoid.hpp ../lab2/lib/deltoid.cpp)
target_link_libraries(Google_Tests_run_lab2 gtest gtest_main lib_deltoid)

#next labs...