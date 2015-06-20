-include config.cache

srcdir ?= .
VPATH = $(srcdir)

CC ?= gcc
CFLAGS ?= -std=c11 -O3 -fPIC -Wall
CXX ?= g++
CXXFLAGS ?= -std=c++11 -O3 -fPIC -Wall
CPPFLAGS ?= -I$(srcdir)/include
LEX ?= flex
LFLAGS ?= -CF -8 -b
CC_FOR_BUILD ?= $(CC)
CFLAGS_FOR_BUILD ?= $(CFLAGS)
CPPFLAGS_FOR_BUILD ?= $(CPPFLAGS)
CXX_FOR_BUILD ?= $(CXX)
CXXFLAGS_FOR_BUILD ?= $(CXXFLAGS)
LDFLAGS_FOR_BUILD ?= $(LDFLAGS)
LDLIBS_FOR_BUILD ?= $(LDLIBS)
prefix ?= /usr/local
separate_build_dir ?= false

includes = \
    include/biting-pear/bbq.h \
    include/biting-pear/kthxbai.h \
    include/biting-pear/lolwut.h \
    include/biting-pear/omg.h

default all: test/test-1

clean:
	find . -name '*.[ios]' -o -name '*~' | \
	    xargs rm -f helper/postproc.cc helper/postproc helper/crc64 \
		lex.backup test/test-1
ifeq "$(separate_build_dir)" "true"
	-rmdir helper test
endif

distclean: clean
	rm -f config.cache
ifeq "$(separate_build_dir)" "true"
	rm -f GNUmakefile
endif

test/test-1: test/test-1.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^ $(LDLIBS)

test/test-1.o: test/test-1.i

%.o: %.i
	$(CXX) $(CXXFLAGS) -c -o$@ $<

# for debugging
%.s: %.i
	$(CXX) $(CXXFLAGS) -S -o$@ $<

%.i: %.ccc $(includes) helper/postproc helper/crc64
	mkdir -p $(@D)
	$(CXX) -E -x c++ $(CPPFLAGS) $(CXXFLAGS) -o$@.tmp $<
	helper/postproc "`helper/crc64 <$@.tmp`" <$@.tmp >$@.2.tmp
	mv $@.2.tmp $@
	rm $@.tmp

helper/crc64: helper/crc64.c
	mkdir -p $(@D)
	$(CC_FOR_BUILD) $(CPPFLAGS_FOR_BUILD) $(CFLAGS_FOR_BUILD) \
	    $(LDFLAGS_FOR_BUILD) -o$@ $< $(LDLIBS_FOR_BUILD)

helper/postproc: helper/postproc.cc
	mkdir -p $(@D)
	$(CXX_FOR_BUILD) $(CPPFLAGS_FOR_BUILD) $(CXXFLAGS_FOR_BUILD) \
	    $(LDFLAGS_FOR_BUILD) -o$@ $< $(LDLIBS_FOR_BUILD)

helper/postproc.cc: helper/postproc.lxx
	mkdir -p $(@D)
	$(LEX) $(LFLAGS) -t -o$@ $< >$@.tmp
	mv $@.tmp $@

.PRECIOUS: %.i %.cc %.s

.PHONY: default all clean distclean
