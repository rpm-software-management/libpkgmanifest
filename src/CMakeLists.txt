file(GLOB_RECURSE libpkgmanifest_SOURCES *.cpp)

list(APPEND libpkgmanifest_PC_REQUIRES)
list(APPEND libpkgmanifest_PC_REQUIRES_PRIVATE)

add_compile_options(-Werror)
include_directories(.)

add_library(libpkgmanifest SHARED ${libpkgmanifest_SOURCES})
set_target_properties(libpkgmanifest PROPERTIES OUTPUT_NAME "pkgmanifest")
set_target_properties(libpkgmanifest PROPERTIES SOVERSION 0)
set_property(TARGET libpkgmanifest PROPERTY POSITION_INDEPENDENT_CODE ON)

install(TARGETS libpkgmanifest LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR})

list(APPEND libpkgmanifest_PC_REQUIRES_PRIVATE "${YAMLCPP_MODULE_NAME}")
list(APPEND libpkgmanifest_PC_REQUIRES_PRIVATE "${RPM_MODULE_NAME}")

target_link_libraries(libpkgmanifest PRIVATE
    PkgConfig::YAMLCPP
    PkgConfig::RPM)

target_link_libraries(libpkgmanifest PUBLIC coverage_config)

list(SORT libpkgmanifest_PC_REQUIRES)
list(JOIN libpkgmanifest_PC_REQUIRES ", " libpkgmanifest_PC_REQUIRES_STRING)
list(SORT libpkgmanifest_PC_REQUIRES_PRIVATE)
list(JOIN libpkgmanifest_PC_REQUIRES_PRIVATE ", " libpkgmanifest_PC_REQUIRES_PRIVATE_STRING)

configure_file("libpkgmanifest.pc.in" ${CMAKE_CURRENT_BINARY_DIR}/libpkgmanifest.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libpkgmanifest.pc DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig)
