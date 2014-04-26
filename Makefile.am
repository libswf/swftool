AM_CFLAGS = -Wall -Wpedantic -Ilib/libswf -lz

SUBDIRS = lib/libswf

bin_PROGRAMS = swftool
swftool_SOURCES = src/main.c src/action_help.c src/action_info.c
swftool_LDADD = lib/libswf/libswf/.libs/libswf.a
