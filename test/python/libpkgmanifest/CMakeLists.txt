add_test(NAME test_python_libpkgmanifest COMMAND ${Python3_EXECUTABLE} -m unittest --verbose WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set_property(TEST test_python_libpkgmanifest PROPERTY ENVIRONMENT
    "PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}"
    "PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}"
    "PYTHONPATH=${CMAKE_BINARY_DIR}/bindings/python"
)