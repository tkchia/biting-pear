-include config.cache

srcdir ?= .

include $(srcdir)/lolwutconf/lolwutconf.mk

includedir = $(prefix)/include

config.h = include/biting-pear/derp.h
headers = \
    include/biting-pear/bbq.h \
    include/biting-pear/kthxbai.h \
    include/biting-pear/lolwut.h \
    include/biting-pear/omg.h \
    $(config.h)

default all: test/test-1

install: $(headers)
	install -d $(includedir)/biting-pear
	install -m 644 $^ $(includedir)/biting-pear

uninstall:
	$(foreach hdr,$(headers), \
	    rm -f $(includedir)/biting-pear/$(notdir $(hdr)) &&) \
	    true
	-rmdir $(includedir)/biting-pear

clean:
	find . -name '*.[ios]' -o -name '*~' | \
	    xargs rm -f $(config.h) helper/postproc.cc helper/postproc \
		helper/crc64 lex.backup test/test-1
ifeq "$(separate_build_dir)" "yes"
	-rmdir helper test
endif

distclean: clean
	rm -f config.cache
ifeq "$(separate_build_dir)" "yes"
	rm -f GNUmakefile
endif

$(config.h):
	mkdir -p $(@D)
	echo "/****** AUTOMATICALLY GENERATED `date` ******/" >$@.tmp
ifeq "$(conf_Have_cxx_typ_std__uint_least64_t)" "yes"
	echo '#include <cinttypes>' >>$@.tmp
else
	echo '#include <inttypes.h>' >>$@.tmp
endif
	echo 'namespace biting_pear { namespace impl {' >>$@.tmp
ifeq "$(conf_Have_cxx_typ_std__uint_least64_t)" "yes"
	echo 'using std::uint_least64_t;' >>$@.tmp
else
	echo 'using ::uint_least64_t;' >>$@.tmp
endif
	echo '} }' >>$@.tmp
	mv $@.tmp $@

test/test-1: test/test-1.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^ $(LDLIBS)

test/test-1.o: test/test-1.i

%.o: %.i
	$(CXX) $(CXXFLAGS) -c -o$@ $<

# for debugging
%.s: %.i
	$(CXX) $(CXXFLAGS) -S -o$@ $<

%.i: %.ccc $(headers) helper/postproc helper/crc64
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
