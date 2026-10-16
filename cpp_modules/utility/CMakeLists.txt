add_library(dsdr_utility STATIC)

target_sources(dsdr_utility
PUBLIC
    FILE_SET CXX_MODULES
    FILES
         ${CMAKE_CURRENT_SOURCE_DIR}/utility.cppm
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/algorithms.cpp
)