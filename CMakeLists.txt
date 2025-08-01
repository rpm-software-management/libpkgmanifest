cmake_minimum_required(VERSION 3.16)

include(VERSION.cmake)

project(libpkgmanifest LANGUAGES CXX VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(WITH_TESTS "Build unit tests" ON)
option(WITH_DOCS "Build documentation" ON)
option(WITH_PYTHON "Build Python bindings" ON)
option(WITH_CODE_COVERAGE "Enable coverage reporting" OFF)

add_library(coverage_config INTERFACE)

if(WITH_CODE_COVERAGE)
  target_compile_options(coverage_config INTERFACE -O0 -g --coverage)
  target_link_options(coverage_config INTERFACE --coverage)
endif()

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)
pkg_check_modules(YAMLCPP REQUIRED IMPORTED_TARGET GLOBAL yaml-cpp)
pkg_check_modules(RPM REQUIRED IMPORTED_TARGET GLOBAL rpm)

add_compile_options(-Wall -Wextra -Werror)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory("bindings")
add_subdirectory("docs")
add_subdirectory("include")
add_subdirectory("src")

enable_testing()
add_subdirectory("test")
