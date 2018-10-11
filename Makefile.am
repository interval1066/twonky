AUTOMAKE_OPTIONS = foreign
CFLAGS = -Wall -c -std=c++11 -I../include
LDFLAGS =

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile
sbin_PROGRAMS = twonky
twonky_SOURCES = src/main.cc src/tgrid.cc src/help.cc
AM_CPPFLAGS = -Wall -c -std=c++11 -I$(top_srcdir)/include
man_MANS = man/twonky.1
EXTRA_DIST = include/twonky.h include/tgrid.h include/config.h man/twonky.1
