AM_CFLAGS = -std=gnu99 -Wall -Wextra -Werror-implicit-function-declaration -pedantic

SUBDIRS = lib/libswf

bin_PROGRAMS = swftool
swftool_SOURCES = src/main.c src/action_help.c src/action_info.c
swftool_LDADD = lib/libswf/libswf/.libs/libswf.a
swftool_LDFLAGS = $(AM_LDFLAGS) -lz
swftool_CFLAGS = $(AM_CFLAGS) -Ilib/libswf
