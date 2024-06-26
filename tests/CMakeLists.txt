if(NOT WITH_TESTS)
    return()
endif()

pkg_check_modules(gtest REQUIRED)
enable_testing()

add_subdirectory(liblockfile)