if(TARGET doctest)
    return()
endif()

include(FetchContent)

set(DOCTEST_VERSION v2.5.3)
FetchContent_Declare(
    doctest
    URL  https://raw.githubusercontent.com/doctest/doctest/${DOCTEST_VERSION}/doctest/doctest.h
    DOWNLOAD_NO_EXTRACT TRUE
)

FetchContent_MakeAvailable(doctest)

set(DOCTEST_INCLUDE_DIR ${doctest_SOURCE_DIR} CACHE INTERNAL "")