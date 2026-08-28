project(DirectorRetainer_tests VERSION 0.0.1 LANGUAGES CXX)

add_executable(dr_tests src/main.cpp)

target_link_libraries(dr_tests PRIVATE DSDR)
target_include_directories(dr_tests PRIVATE 
${DOCTEST_INCLUDE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/unit_tests
)


add_custom_command(
    OUTPUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data/databases/example_monster_database.toml"
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/test_data/example_monster_database.toml"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data/databases/example_monster_database.toml"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test_data/example_monster_database.toml"
    
)

add_custom_command(
    OUTPUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data/databases/example_monster_database.json"
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/test_data/example_monster_database.json"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data/databases/example_monster_database.json"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test_data/example_monster_database.json"
    
)


# Custom target for activate the custom command above
add_custom_target(copy_config DEPENDS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data/databases/example_monster_database.toml" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_data/databases/example_monster_database.json")
add_dependencies(dr_tests copy_config)

