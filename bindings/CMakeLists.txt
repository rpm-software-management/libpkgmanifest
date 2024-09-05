if(NOT WITH_PYTHON)
    return()
endif()

message("Building bindings")

cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)

find_package(Python3 REQUIRED)
find_package(SWIG REQUIRED)
include(UseSWIG)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SWIG_COMPILE_OPTIONS
    -Wno-missing-field-initializers
)

add_subdirectory(python)