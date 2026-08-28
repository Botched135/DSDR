if(TARGET rapidfuzz::rapidfuzz)
    return()
endif()

include(FetchContent)

FetchContent_Declare(
    rapidfuzz
    GIT_REPOSITORY https://github.com/rapidfuzz/rapidfuzz-cpp.git
    GIT_TAG        v3.3.3
)

FetchContent_MakeAvailable(rapidfuzz)