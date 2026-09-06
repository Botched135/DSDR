add_library(ds_database_module STATIC)

target_sources(ds_database_module
PUBLIC
    FILE_SET CXX_MODULES
    FILES
         "${CMAKE_CURRENT_SOURCE_DIR}/database.ixx"
PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/databases/creature_db.cpp"
)


add_executable(ds_database main.cpp)
target_link_libraries(ds_database ds_database_module)