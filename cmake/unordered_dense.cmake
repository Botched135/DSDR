if(TARGET unordered_dense::unordered_dense)
    return()
endif()

include(FetchContent)

FetchContent_Declare(
    unordered_dense
    GIT_REPOSITORY https://github.com/martinus/unordered_dense.git
    GIT_TAG        v4.9.2
)

FetchContent_MakeAvailable(unordered_dense)