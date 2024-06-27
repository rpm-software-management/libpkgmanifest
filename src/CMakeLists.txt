file(GLOB_RECURSE LIBLOCKFILE_SOURCES *.cpp)

include_directories(.)

add_library(liblockfile SHARED ${LIBLOCKFILE_SOURCES})