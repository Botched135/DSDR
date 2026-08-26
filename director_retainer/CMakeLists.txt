project(DirectorRetainer VERSION 0.0.1 LANGUAGES CXX)


add_executable(director_retainer WIN32 src/DirectorRetainer.cpp)

target_link_libraries(director_retainer PRIVATE SDL3::SDL3 fmt::fmt unordered_dense::unordered_dense tomlplusplus::tomlplusplus rapidfuzz::rapidfuzz)