# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(googletest-main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#tests for lab2
include_directories(../lab2/lib)
add_executable(Google_Tests_run_lab2 ../lab2/test/test.cpp)
target_link_libraries(Google_Tests_run_lab2 gtest gtest_main lib_deltoid)

#tests for lab3.2
include_directories(../lab3.2/lib)
add_executable(Google_Tests_run_lab3.2 ../lab3.2/test/test.cpp)
target_link_libraries(Google_Tests_run_lab3.2 gtest gtest_main lib_circuitboard)

#tests for lab3.3
include_directories(../lab3.3/lib)
add_executable(Google_Tests_run_lab3.3 ../lab3.3/test/test.cpp)
target_link_libraries(Google_Tests_run_lab3.3 gtest gtest_main lib_pcb)
#next labs...