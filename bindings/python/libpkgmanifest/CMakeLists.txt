message("Building bindings for Python: libpkgmanifest")

set(INIT_FILE "${CMAKE_CURRENT_BINARY_DIR}/__init__.py")
file(REMOVE "${INIT_FILE}")
foreach(MODULE_NAME ${SWIG_LIBPKGMANIFEST_MODULES})
    add_python_module(libpkgmanifest ${MODULE_NAME})
    file(APPEND "${INIT_FILE}" "from . import ${MODULE_NAME}\n")
endforeach()


install(FILES "${INIT_FILE}" DESTINATION ${Python3_SITEARCH}/libpkgmanifest)
