project(DirectorRetainer VERSION 0.0.1 LANGUAGES CXX)


add_executable(director_retainer WIN32 src/DirectorRetainer.cpp)

target_sources(director_retainer PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/MonsterDB.hpp"
)

target_sources(director_retainer PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/MonsterDB.cpp"
)


add_custom_command(TARGET director_retainer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_SOURCE_DIR}/data/databases/example_database.toml"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/databases/example_database.toml"
)

target_link_libraries(director_retainer PRIVATE SDL3::SDL3 imgui fmt::fmt unordered_dense::unordered_dense tomlplusplus::tomlplusplus rapidfuzz::rapidfuzz utility_headers)