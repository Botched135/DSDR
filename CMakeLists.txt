cmake_minimum_required(VERSION 3.15)

project(DSDR VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_FLAGS_RELEASE "/Ox") # This might only be for windows


# Setting 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>" CACHE INTERNAL "")


include(FetchContent)

FetchContent_Declare(
    SDL EXCLUDE_FROM_ALL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.14
)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.92.9
)

FetchContent_Declare(
    unordered_dense
    GIT_REPOSITORY https://github.com/martinus/unordered_dense.git
    GIT_TAG        v4.9.2
)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG        v3.4.0
)

FetchContent_Declare(
    rapidfuzz
    GIT_REPOSITORY https://github.com/rapidfuzz/rapidfuzz-cpp.git
    GIT_TAG        v3.3.3
)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        12.2.0
) 

set(DOCTEST_VERSION v2.5.3)
FetchContent_Declare(
    doctest
    URL  https://raw.githubusercontent.com/doctest/doctest/${DOCTEST_VERSION}/doctest/doctest.h
    DOWNLOAD_NO_EXTRACT TRUE
)

FetchContent_MakeAvailable(SDL imgui unordered_dense tomlplusplus rapidfuzz fmt doctest)

set(DOCTEST_INCLUDE_DIR ${doctest_SOURCE_DIR} CACHE INTERNAL "")

add_library(imgui STATIC)

target_include_directories(imgui PUBLIC 
${imgui_SOURCE_DIR}
${imgui_SOURCE_DIR}/backends
)

target_sources(imgui PUBLIC
${imgui_SOURCE_DIR}/imgui.cpp
${imgui_SOURCE_DIR}/imgui_demo.cpp
${imgui_SOURCE_DIR}/imgui_draw.cpp
${imgui_SOURCE_DIR}/imgui_tables.cpp
${imgui_SOURCE_DIR}/imgui_widgets.cpp
${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

target_link_libraries(imgui PUBLIC SDL3::SDL3)



add_library(utility_headers INTERFACE)
target_include_directories(utility_headers INTERFACE ${PROJECT_SOURCE_DIR}/utility)

add_subdirectory(director_retainer)
add_subdirectory(tests)