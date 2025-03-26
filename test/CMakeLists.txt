if(NOT WITH_TESTS)
    return()
endif()

pkg_check_modules(GTEST REQUIRED gtest)
pkg_check_modules(GMOCK REQUIRED gmock)

file(GLOB_RECURSE TEST_libpkgmanifest_SOURCES *.cpp)

include_directories(.)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(libpkgmanifest_tests_runner ${TEST_libpkgmanifest_SOURCES})

target_link_libraries(libpkgmanifest_tests_runner PRIVATE libpkgmanifest gtest gmock yaml-cpp)

add_test(NAME tests_libpkgmanifest COMMAND libpkgmanifest_tests_runner)

set_property(TEST tests_libpkgmanifest PROPERTY ENVIRONMENT
    "PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}"
    "PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}"
)

add_subdirectory("python")