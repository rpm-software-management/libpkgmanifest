if(NOT WITH_PYTHON)
    return()
endif()

find_package(Python3 REQUIRED)

add_subdirectory(libpkgmanifest)