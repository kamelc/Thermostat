cmake_minimum_required(VERSION 3.10)
set(APP "Thermostat")
project (${APP} LANGUAGES CXX)
include_directories(../inc)
# Create a sources variable with a link to all cpp files to compile
 file(GLOB SOURCES
     "*.cpp"
 )

add_library(${APP}_lib STATIC ${SOURCES})
target_include_directories(${APP}_lib PUBLIC include)