message("Building bindings for Python")

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
include_directories(${Python3_INCLUDE_DIRS})

function(add_python_module MODULE_NAME)
    set_source_files_properties(../${MODULE_NAME}.i PROPERTIES CPLUSPLUS ON)
    swig_add_library(${MODULE_NAME} LANGUAGE python SOURCES ../${MODULE_NAME}.i)
    swig_link_libraries(${MODULE_NAME} ${C_LIBRARY_NAME})
    swig_link_libraries(${MODULE_NAME} ${Python3_LIBRARIES})

    set(DISTINFO_PATH "${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}-${CMAKE_PROJECT_VERSION}.dist-info")
    set(METADATA_FILE "${DISTINFO_PATH}/METADATA")
    file(MAKE_DIRECTORY ${DISTINFO_PATH})
    file(WRITE ${METADATA_FILE} "Metadata-Version: 2.3\n")
    file(APPEND ${METADATA_FILE} "Name: ${MODULE_NAME}\n")
    file(APPEND ${METADATA_FILE} "Version: ${CMAKE_PROJECT_VERSION}\n")

    install(TARGETS ${MODULE_NAME} LIBRARY DESTINATION ${Python3_SITEARCH})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}.py DESTINATION ${Python3_SITEARCH})
    install(DIRECTORY ${DISTINFO_PATH} DESTINATION ${Python3_SITEARCH})
endfunction()

add_python_module(liblockfile)