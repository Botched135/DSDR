cmake_minimum_required(VERSION 3.15)

project(DSDR VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS_RELEASE "/Ox") # This might only be for windows


add_library(utility_headers INTERFACE)
target_include_directories(utility_headers INTERFACE ${PROJECT_SOURCE_DIR})

add_subdirectory(director_retainer)
add_subdirectory(tests)