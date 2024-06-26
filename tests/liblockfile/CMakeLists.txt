file(GLOB_RECURSE TEST_LIBLOCKFILE_SOURCES *.cpp)

include_directories(${PROJECT_SOURCE_DIR}/src/liblockfile)

add_executable(liblockfile_tests_runner ${TEST_LIBLOCKFILE_SOURCES})

target_link_libraries(liblockfile_tests_runner PRIVATE liblockfile gtest)

add_test(NAME tests_liblockfile COMMAND liblockfile_tests_runner)