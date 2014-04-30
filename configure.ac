AC_INIT([swftool], [0.0.1])
AM_INIT_AUTOMAKE([subdir-objects foreign])

AC_PROG_CC

AC_CONFIG_FILES(Makefile)

PKG_CHECK_MODULES([LIBSWF], libswf >= 0.0.0, [
	CFLAGS="$CFLAGS $LIBSWF_CFLAGS"
	LIBS="$LIBS $LIBSWF_LIBS"
	AC_DEFINE(CONFIG_LIBSWF, 1, [found libswf via pkg-config])
])

# This makes it error out for... some reason
#AX_CHECK_ZLIB()

AC_OUTPUT
