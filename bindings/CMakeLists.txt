if(NOT WITH_PYTHON)
    return()
endif()

message("Building bindings")

cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)

find_package(SWIG REQUIRED)
include(UseSWIG)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(python)