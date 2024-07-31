if(NOT WITH_TESTS)
    return()
endif()

pkg_check_modules(GTEST REQUIRED gtest)
enable_testing()

file(GLOB_RECURSE TEST_LIBLOCKFILE_SOURCES *.cpp)

include_directories(./api)
include_directories(./impl)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src/impl)

add_executable(liblockfile_tests_runner ${TEST_LIBLOCKFILE_SOURCES})

target_link_libraries(liblockfile_tests_runner PRIVATE liblockfile gtest gmock yaml-cpp)

add_test(NAME tests_liblockfile COMMAND liblockfile_tests_runner)