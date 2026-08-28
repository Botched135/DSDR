if(TARGET SDL3::SDL3)
    return()
endif()

include(FetchContent)

FetchContent_Declare(
    SDL EXCLUDE_FROM_ALL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.4.14
)

FetchContent_MakeAvailable(SDL)