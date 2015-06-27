VPATH = $(srcdir)

export SHELL ?= /bin/sh
export CC ?= gcc
export CFLAGS ?= -std=c11 -O3 -fPIC -Wall
export CXX ?= g++
export CXXFLAGS ?= -std=c++11 -O3 -fPIC -Wall
export CPPFLAGS ?= -I$(srcdir)/include
export LEX ?= flex
export LFLAGS ?= -CF -8 -b
export CC_FOR_BUILD ?= $(CC)
export CFLAGS_FOR_BUILD ?= $(CFLAGS)
export CPPFLAGS_FOR_BUILD ?= $(CPPFLAGS)
export CXX_FOR_BUILD ?= $(CXX)
export CXXFLAGS_FOR_BUILD ?= $(CXXFLAGS)
export LDFLAGS_FOR_BUILD ?= $(LDFLAGS)
export LDLIBS_FOR_BUILD ?= $(LDLIBS)

prefix ?= /usr/local
ifeq "." "$(srcdir)"
    separate_build_dir ?= no
else
    separate_build_dir ?= yes
endif
includedir = $(prefix)/include

.DEFAULT_GOAL := default

.PHONY: default all install uninstall clean distclean
