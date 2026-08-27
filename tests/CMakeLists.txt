# This requires doctest
project(DirectorRetainer_tests VERSION 0.0.1 LANGUAGES CXX)

add_executable(dr_tests src/main.cpp)

target_link_libraries(dr_tests PRIVATE DSDR)
target_include_directories(dr_tests PRIVATE 
${DOCTEST_INCLUDE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/unit_tests
)

add_custom_command(TARGET dr_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/test_data/example_monster_database.toml"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data/databases/example_monster_database.toml"
)

add_custom_command(TARGET dr_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/test_data/example_monster_database.json"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data/databases/example_monster_database.json"
)

