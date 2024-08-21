file(GLOB_RECURSE libpkgmanifest_HEADERS *.hpp)

foreach(abspath ${libpkgmanifest_HEADERS})
    file(RELATIVE_PATH relpath ${CMAKE_CURRENT_SOURCE_DIR} ${abspath})
    get_filename_component(relpath_dir ${relpath} DIRECTORY)
    install(FILES ${abspath} DESTINATION include/libpkgmanifest/${relpath_dir})
endforeach()