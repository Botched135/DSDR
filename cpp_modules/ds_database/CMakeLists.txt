add_library(ds_database_module STATIC)

target_sources(ds_database_module
PUBLIC
    FILE_SET CXX_MODULES
    FILES
         ${CMAKE_CURRENT_SOURCE_DIR}/database.cppm
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/databases/creature_db.cppm
    ${CMAKE_CURRENT_SOURCE_DIR}/convertion/convertion_maps.cppm
)

target_link_libraries(ds_database_module dsdr_utility)

add_executable(ds_database main.cpp)
target_link_libraries(ds_database ds_database_module)