project(DirectorRetainer VERSION 0.0.1 LANGUAGES CXX)


add_executable(director_retainer WIN32 director_retainer.cpp)

add_custom_command(TARGET director_retainer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_SOURCE_DIR}/data/databases/example_database.toml"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/databases/example_database.toml"
)

target_link_libraries(director_retainer PRIVATE DSDR)