file(GLOB swftool_SOURCES *.c *.h)
add_executable(swftool ${swftool_SOURCES})

find_library(libswf swf)
find_library(libz z)
target_link_libraries(swftool ${libswf} ${libz})
