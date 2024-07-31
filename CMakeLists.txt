cmake_minimum_required(VERSION 3.10)

include(VERSION.cmake)

project(liblockfile LANGUAGES CXX VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(WITH_TESTS "Build unit tests" ON)
option(WITH_DOCS "Build documentation" ON)
option(WITH_PYTHON "Build Python bindings" ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp)

add_compile_options(-Wall -Wextra -Werror)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory("bindings")
add_subdirectory("docs")
add_subdirectory("include")
add_subdirectory("src")
add_subdirectory("tests")
