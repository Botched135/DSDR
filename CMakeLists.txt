cmake_minimum_required(VERSION 3.15)

project(DSDR VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS_RELEASE "/Ox") # This might only be for windows

# Setting 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>" CACHE INTERNAL "")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(SDL)
include(imgui)
include(fmt)
include(rapidfuzz)
include(tomlplusplus)
include(unordered_dense)
include(doctest)


add_library(DSDR STATIC)

target_include_directories(DSDR PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(DSDR PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ds_enum_converters.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database/monster_db.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/management/encounter_management.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/management/malice_management.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/management/round_management.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/management/turn_management.cpp
)

target_link_libraries(DSDR PUBLIC SDL3::SDL3 imgui fmt::fmt unordered_dense::unordered_dense tomlplusplus::tomlplusplus rapidfuzz::rapidfuzz)


add_subdirectory(director_retainer)
add_subdirectory(tests)