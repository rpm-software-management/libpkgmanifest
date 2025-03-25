message("Building bindings for Python")

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
include_directories(${Python3_INCLUDE_DIRS})

function(add_python_module LIBRARY_NAME MODULE_NAME)
    set(TARGET_NAME "python3_${MODULE_NAME}")
    list(APPEND CMAKE_SWIG_FLAGS -doxygen)
    set_source_files_properties(../../${LIBRARY_NAME}/${MODULE_NAME}.i PROPERTIES CPLUSPLUS ON)
    swig_add_library(${TARGET_NAME} LANGUAGE python SOURCES ../../${LIBRARY_NAME}/${MODULE_NAME}.i)
    set_property(TARGET ${TARGET_NAME} PROPERTY OUTPUT_NAME ${MODULE_NAME})
    target_compile_options(${TARGET_NAME} PUBLIC ${SWIG_COMPILE_OPTIONS})
    target_link_libraries(${TARGET_NAME} PRIVATE ${LIBRARY_NAME})
    target_link_libraries(${TARGET_NAME} PRIVATE ${Python3_LIBRARIES})

    install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION ${Python3_SITEARCH}/${LIBRARY_NAME})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${MODULE_NAME}.py DESTINATION ${Python3_SITEARCH}/${LIBRARY_NAME})
endfunction()

function(add_distinfo_metadata LIBRARY_NAME)
    set(DISTINFO_PATH "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}-${CMAKE_PROJECT_VERSION}.dist-info")
    set(METADATA_FILE "${DISTINFO_PATH}/METADATA")
    file(MAKE_DIRECTORY ${DISTINFO_PATH})
    file(WRITE ${METADATA_FILE} "Metadata-Version: 2.3\n")
    file(APPEND ${METADATA_FILE} "Name: ${LIBRARY_NAME}\n")
    file(APPEND ${METADATA_FILE} "Version: ${CMAKE_PROJECT_VERSION}\n")

    install(DIRECTORY ${DISTINFO_PATH} DESTINATION ${Python3_SITEARCH})
endfunction()

add_distinfo_metadata(libpkgmanifest)

add_subdirectory(libpkgmanifest)
