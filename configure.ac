AC_INIT([eConsole], [1.0], [john-warnes@github.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AX_CHECK_COMPILE_FLAG([-std=c11], [
  CFLAGS+=' -std=c11'
], [
  echo "C compiler cannot compile C11 code"
  exit -1
])
AC_LANG(C)
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_OUTPUT
