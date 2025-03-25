if(NOT WITH_DOCS)
    return()
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in ${CMAKE_CURRENT_BINARY_DIR}/conf.py)

add_custom_target(doc)

add_custom_target(doxygen
    doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    COMMENT "Building doxygen xml files"
)

add_custom_target(doc-html
    sphinx-build -c ${CMAKE_CURRENT_BINARY_DIR} -b html
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/html
    COMMENT "Building html documentation"
)

add_dependencies(doc doc-html)
add_dependencies(doc-html doxygen)
