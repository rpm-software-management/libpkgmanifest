file(GLOB_RECURSE LIBLOCKFILE_SOURCES *.cpp)

include_directories(./api)
include_directories(./impl)

add_library(lockfile SHARED ${LIBLOCKFILE_SOURCES})