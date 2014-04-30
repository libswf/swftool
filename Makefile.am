AM_CFLAGS = -std=gnu99 -Wall -Wextra -Werror-implicit-function-declaration -Wno-unused-parameter -pedantic

bin_PROGRAMS = swftool
swftool_SOURCES = src/main.c src/action_help.c src/action_info.c
swftool_CFLAGS = $(AM_CFLAGS) -Ilib/libswf -ggdb -O0
