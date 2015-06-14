CFLAGS = -std=c11 -O3 -fPIC -Wall
CXXFLAGS = -std=c++11 -O3 -fPIC -Wall
CPPFLAGS = -I.
LEX = flex
LFLAGS = -CF -8 -b

includes = \
    biting-pear/bbq.h \
    biting-pear/kthxbai.h \
    biting-pear/lolwut.h \
    biting-pear/omg.h

default all: test-1

clean:
	find . -name '*.[ios]' -o -name '*~' | \
	    xargs rm -f helper/postproc.cc helper/postproc helper/crc64 \
		lex.backup test-1

test-1: test-1.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^

test-1.o: test-1.i

%.o: %.i
	$(CXX) $(CXXFLAGS) -c -o$@ $<

# for debugging
%.s: %.i
	$(CXX) $(CXXFLAGS) -S -o$@ $<

%.i: %.ccc $(includes) helper/postproc helper/crc64
	$(CXX) -E -x c++ $(CPPFLAGS) $(CXXFLAGS) -o$@.tmp $<
	helper/postproc "`helper/crc64 <$@.tmp`" <$@.tmp >$@.2.tmp
	mv $@.2.tmp $@
	rm $@.tmp

helper/crc64: helper/crc64.c

helper/postproc: helper/postproc.cc

helper/postproc.cc: helper/postproc.ll
	$(LEX) $(LFLAGS) -t -o$@ $< >$@.tmp
	mv $@.tmp $@

.PRECIOUS: %.i %.cc %.s

.PHONY: default all clean
