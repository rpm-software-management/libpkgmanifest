message("Building bindings for Python")

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
include_directories(${Python3_INCLUDE_DIRS})

function(add_python_module LIBRARY_NAME WRAPPER_NAME)
    set(TARGET_NAME "python3_${WRAPPER_NAME}")
    set_source_files_properties(../${WRAPPER_NAME}.i PROPERTIES CPLUSPLUS ON)
    swig_add_library(${TARGET_NAME} LANGUAGE python SOURCES ../${WRAPPER_NAME}.i)
    set_property(TARGET ${TARGET_NAME} PROPERTY OUTPUT_NAME ${WRAPPER_NAME})
    target_compile_options(${TARGET_NAME} PUBLIC ${SWIG_COMPILE_OPTIONS})
    target_link_libraries(${TARGET_NAME} PRIVATE ${LIBRARY_NAME})
    target_link_libraries(${TARGET_NAME} PRIVATE ${Python3_LIBRARIES})

    set(DISTINFO_PATH "${CMAKE_CURRENT_BINARY_DIR}/${WRAPPER_NAME}-${CMAKE_PROJECT_VERSION}.dist-info")
    set(METADATA_FILE "${DISTINFO_PATH}/METADATA")
    file(MAKE_DIRECTORY ${DISTINFO_PATH})
    file(WRITE ${METADATA_FILE} "Metadata-Version: 2.3\n")
    file(APPEND ${METADATA_FILE} "Name: ${WRAPPER_NAME}\n")
    file(APPEND ${METADATA_FILE} "Version: ${CMAKE_PROJECT_VERSION}\n")

    install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION ${Python3_SITEARCH})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${WRAPPER_NAME}.py DESTINATION ${Python3_SITEARCH})
    install(DIRECTORY ${DISTINFO_PATH} DESTINATION ${Python3_SITEARCH})
endfunction()

add_python_module(libpkgmanifest libpkgmanifest)