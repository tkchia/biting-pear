-include config.cache

srcdir ?= .

include $(srcdir)/lolwutconf/lolwutconf.mk

includedir = $(prefix)/include

config.h = include/biting-pear/derp.h
headers = \
    include/biting-pear/bbq.h \
    include/biting-pear/dawg.h \
    include/biting-pear/kthxbai.h \
    include/biting-pear/lolwut.h \
    include/biting-pear/nowai.h \
    include/biting-pear/omg.h \
    include/biting-pear/orly.h \
    include/biting-pear/yarly.h \
    include/biting-pear/yodawg.h \
    $(config.h)
tests = \
    test/test-1 \
    test/test-2 \
    test/test-3
ifeq "$(conf_Have_cxx_var_tpls)" "yes"
tests += \
    test/test-extra-1 \
    test/test-extra-2 \
    test/test-extra-3 \
    test/test-extra-4
endif

default all: check

check: $(tests:=.passed)

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
	    xargs rm -f config.cache $(config.h) helper/postpreproc.cc \
		helper/postpreproc helper/crc64 lex.backup \
		$(tests) $(tests:=.passed)
ifeq "$(separate_build_dir)" "yes"
	-rmdir helper test
endif

distclean: clean
	rm -f config.cache
ifeq "$(separate_build_dir)" "yes"
	rm -f GNUmakefile
endif

config.cache:
	./configure

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
ifeq "$(conf_Have_cxx_var_tpls)" "yes"
	echo '#define biting_pear_HAVE_CXX_VAR_TPLS 1' >>$@.tmp
else
	echo '#undef biting_pear_HAVE_CXX_VAR_TPLS' >>$@.tmp
endif
ifeq "$(conf_Have_cxx_decltype)" "yes"
	echo '#define biting_pear_decltype decltype' >>$@.tmp
else
	echo '#define biting_pear_decltype __typeof' >>$@.tmp
endif
	mv $@.tmp $@

test/test-%.passed: test/test-% test/test-%.good
	@echo "running test $<" >&2
	@LANG=en_US.UTF-8 $(conf_Host_exec) ./$< >$(@:.passed=.1.tmp) \
	    2>$(@:.passed=.2.tmp) ||\
	    (echo "$< exited with error: $$?" >&2 && \
	     rm -f $(@:.passed=.1.tmp) $(@:.passed=.2.tmp) && \
	     exit 1)
	@LANG=en_US.UTF-8 diff -U2 /dev/null $(@:.passed=.2.tmp) || \
	    (echo "$< produced output on stderr" >&2 && \
	     rm -f $(@:.passed=.1.tmp) $(@:.passed=.2.tmp) && \
	     exit 1)
	@LANG=en_US.UTF-8 diff -U2 $<.good $(@:.passed=.1.tmp) || \
	    (echo "$<'s expected output and actual output differ" >&2 && \
	     rm -f $(@:.passed=.1.tmp) $(@:.passed=.2.tmp) && \
	     exit 1)
	@echo "$< passed"
	@rm -f $(@:.passed=.1.tmp) $(@:.passed=.2.tmp)

test/test-%: test/test-%.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^ $(LDLIBS)

test/test-%.o: test/test-%.i

%.o: %.i
	$(CXX) $(CXXFLAGS) -c -o$@ $<

# for debugging
%.s: %.i
	$(CXX) $(CXXFLAGS) -S -o$@ $<

%.i: %.ccc $(headers) helper/postpreproc helper/crc64
	mkdir -p $(@D)
	$(CXX) -E -x c++ $(CPPFLAGS) $(CXXFLAGS) -o$@.tmp $<
	$(conf_Host_exec) helper/postpreproc \
	    "`$(conf_Host_exec) helper/crc64 <$@.tmp`" <$@.tmp \
	    >$@.2.tmp
	mv $@.2.tmp $@
	rm $@.tmp

helper/%: helper/%.cc
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o$@ $< $(LDLIBS)

helper/postpreproc.cc: helper/postpreproc.lxx
	mkdir -p $(@D)
	$(LEX) $(LFLAGS) -t -o$@ $< >$@.tmp
	mv $@.tmp $@

.PHONY: test/test-%.passed

.PRECIOUS: config.cache %.i %.cc %.s %.o helper/% $(tests)
