cmake_minimum_required(VERSION 3.10)
project(Thermostat_test)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../inc)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests Thermostat_tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ${APP}_lib)
