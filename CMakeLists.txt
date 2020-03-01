cmake_minimum_required(VERSION 3.15)
project(gtest_sample)

add_subdirectory(external/googletest)

set(CMAKE_CXX_STANDARD 14)

add_custom_target(check COMMAND GTEST_COLOR=1 ctest --verbose)

add_executable(gtest_sample main.cpp)


enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(gtest_test inputTest.cpp)
target_link_libraries(gtest_test gtest gtest_main)