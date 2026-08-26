# This requires doctest
project(DirectorRetainer_tests VERSION 0.0.1 LANGUAGES CXX)

add_executable(dr_tests src/main.cpp)

target_include_directories(dr_tests PUBLIC ${DOCTEST_INCLUDE_DIR})