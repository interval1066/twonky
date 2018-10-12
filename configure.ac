#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([twonky], [1.0], [interval1066@gmail.com])
AM_INIT_AUTOMAKE([subdir-objects])
AC_OUTPUT(Makefile)
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_LANG(C++)
AC_LANG_PUSH([C++])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],[])],[],[AC_MSG_ERROR([No C++ compiler found])])
AC_LANG_POP([C++])

# Checks for libraries.

# C/C++ Language Features
AC_C_CONST
AC_C_INLINE
AC_C_VOLATILE

# C/C++ Headers
AC_HEADER_STDC
AC_HEADER_STDBOOL

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([sqrt])

AC_OUTPUT
