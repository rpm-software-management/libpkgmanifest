file(GLOB_RECURSE LIBLOCKFILE_HEADERS *.hpp)

foreach(abspath ${LIBLOCKFILE_HEADERS})
    file(RELATIVE_PATH relpath ${CMAKE_CURRENT_SOURCE_DIR} ${abspath})
    get_filename_component(relpath_dir ${relpath} DIRECTORY)
    install(FILES ${abspath} DESTINATION include/liblockfile/${relpath_dir})
endforeach()