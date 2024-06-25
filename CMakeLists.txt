cmake_minimum_required(VERSION 3.10)

include(VERSION.cmake)

project(liblockfile LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(WITH_TESTS "Build unit tests" ON)
option(WITH_DOCS "Build documentation" ON)
option(WITH_PYTHON "Build Python bindings" ON)

add_compile_options(-Wall -Wextra -Werror)

add_subdirectory("bindings")
add_subdirectory("docs")
add_subdirectory("include")
add_subdirectory("lib")
add_subdirectory("tests")