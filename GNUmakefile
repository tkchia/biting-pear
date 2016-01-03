-include config.cache

conf_Srcdir ?= .
include $(conf_Srcdir)/lolwutconf/lolwutconf.mk

libexecdir = $(conf_Prefix)/libexec
includedir.target = $(conf_Target_prefix)/include

config.h.host = include/biting-pear/host/derp.h
headers.host = \
    include/biting-pear/bbq.h \
    include/biting-pear/nowai.h \
    include/biting-pear/host/rly.h \
    include/biting-pear/host/srsly.h \
    $(config.h.host)
config.h.target = include/biting-pear/derp.h
headers.target = \
    include/biting-pear/bbq.h \
    include/biting-pear/dawg.h \
    include/biting-pear/kthxbai.h \
    include/biting-pear/lolwut.h \
    include/biting-pear/nowai.h \
    include/biting-pear/omg.h \
    include/biting-pear/orly.h \
    include/biting-pear/yarly.h \
    include/biting-pear/yodawg.h \
    $(config.h.target)
tests.target = \
    test/test-1 \
    test/test-2 \
    test/test-3
ifeq "$(conf_Have_cxxt_var_tpls)" "yes"
tests.target += \
    test/test-extra-1 \
    test/test-extra-2 \
    test/test-extra-3 \
    test/test-extra-4
endif
utils.host = \
    libexec/biting-pear/nomnom \
    libexec/biting-pear/omnomnom
ifeq "$(conf_Have_cxx_typ_struct_bfd)" "yes"
ifeq "$(conf_Have_cxx_lib_bfd)" "yes"
ifeq "$(conf_Have_cxx_var_tpls)" "yes"
utils.host += \
    libexec/biting-pear/doge
endif
endif
endif

default all: check

check: $(tests.target:=.passed) $(utils.host)

install: install-host-files install-target-files

install-host-files:

install-target-files: $(headers.target)
	install -d $(includedir.target)/biting-pear
	install -m 644 $^ $(includedir.target)/biting-pear

uninstall:
	$(foreach hdr,$(headers.target), \
	    rm -f $(includedir.target)/biting-pear/$(notdir $(hdr)) &&) \
	    true
	-rmdir $(includedir.target)/biting-pear $(libexecdir)/biting-pear

clean:
	find . -name '*.[ios]' -o -name '*~' | \
	    xargs rm -f config.cache $(config.h.host) $(config.h.target) \
		lex.backup libexec/biting-pear/omnomnom.cc \
		$(tests.target) $(utils.host)
ifeq "$(conf_Separate_build_dir)" "yes"
	-rmdir helper test util
endif

distclean: clean
	rm -f config.cache
ifeq "$(conf_Separate_build_dir)" "yes"
	rm -f GNUmakefile
endif

config.cache:
	./configure

$(config.h.host) $(config.h.target):
	mkdir -p $(@D)
	echo "/****** AUTOMATICALLY GENERATED `date` ******/" >$@.tmp
	if test '$(conf_Have_cxx_typ_std__uint_least64_t),$@' = \
	    'yes,$(config.h.host)'; then \
		echo '#include <cinttypes>' >>$@.tmp; \
	elif test '$(conf_Have_cxxt_typ_std__uint_least64_t),$@' = \
	    'yes,$(config.h.target)'; then \
		echo '#include <cinttypes>' >>$@.tmp; \
	else \
		echo '#include <inttypes.h>' >>$@.tmp; \
	fi
	echo 'namespace biting_pear { namespace impl {' >>$@.tmp
	if test '$(conf_Have_cxx_typ_std__uint_least64_t),$@' = \
	    'yes,$(config.h.host)'; then \
		echo 'using std::uint_least64_t;' >>$@.tmp; \
	elif test '$(conf_Have_cxxt_typ_std__uint_least64_t),$@' = \
	    'yes,$(config.h.target)'; then \
		echo 'using std::uint_least64_t;' >>$@.tmp; \
	else \
		echo 'using ::uint_least64_t;' >>$@.tmp; \
	fi
	echo '} }' >>$@.tmp
	if test x'$@' = x'$(config.h.host)'; then \
		if test '$(conf_Typ_wchar_cxx)' = '$(conf_Typ_wchar_cxxt)' \
		     -a unknown != '$(conf_Typ_wchar_cxx)'; then \
			echo '#define biting_pear_TARGET_COMPATIBLE_WCHAR 1';\
		else \
			echo '#define biting_pear_TARGET_COMPATIBLE_WCHAR 0';\
		fi >>$@.tmp; \
	fi
	if test '$(conf_Have_cxx_var_tpls),$@' = 'yes,$(config.h.host)'; then\
		echo '#define biting_pear_HAVE_CXX_VAR_TPLS 1' >>$@.tmp; \
	elif test '$(conf_Have_cxxt_var_tpls),$@' = \
	    'yes,$(config.h.target)'; then \
		echo '#define biting_pear_HAVE_CXX_VAR_TPLS 1' >>$@.tmp; \
	else \
		echo '#undef biting_pear_HAVE_CXX_VAR_TPLS' >>$@.tmp; \
	fi
	if test '$(conf_Have_cxx_decltype,$@)' = 'yes,$(config.h.host)'; then\
		echo '#define biting_pear_decltype decltype' >>$@.tmp; \
	elif test '$(conf_Have_cxxt_decltype,$@)' = \
	    'yes,$(config.h.target)'; then\
		echo '#define biting_pear_decltype decltype' >>$@.tmp; \
	else \
		echo '#define biting_pear_decltype __typeof' >>$@.tmp; \
	fi
	mv $@.tmp $@

test/test-%.passed: test/test-% test/test-%.good
	@echo "running test $<" >&2
	@LANG=en_US.UTF-8 $(conf_Target_exec) ./$< >$(@:.passed=.1.tmp) \
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
	$(CXX_FOR_TARGET) $(CXXFLAGS_FOR_TARGET) $(LDFLAGS_FOR_TARGET) \
	    -o$@ $^ $(LDLIBS_FOR_TARGET)

test/test-%.o: test/test-%.i

libexec/biting-pear/%: libexec/biting-pear/%.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^ $(LDLIBS)

libexec/biting-pear/%.o: libexec/biting-pear/%.i
	$(CXX) $(CXXFLAGS) -c -o$@ $<

libexec/biting-pear/%.i: libexec/biting-pear/%.ccc $(headers.host) \
    $(headers.target) libexec/biting-pear/omnomnom libexec/biting-pear/nomnom
	mkdir -p $(@D)
	$(CXX) -E -x c++ $(CPPFLAGS) $(CXXFLAGS) -o$@.tmp $<
	$(conf_Host_exec) libexec/biting-pear/omnomnom \
	    "`$(conf_Host_exec) libexec/biting-pear/nomnom <$@.tmp`" \
	    <$@.tmp >$@.2.tmp
	mv $@.2.tmp $@
	rm $@.tmp

libexec/biting-pear/omnomnom.o: libexec/biting-pear/omnomnom.cc \
    $(config.h.host)

%.o: %.i
	$(CXX_FOR_TARGET) $(CXXFLAGS_FOR_TARGET) -c -o$@ $<

# for debugging
%.s: %.i
	$(CXX_FOR_TARGET) $(CXXFLAGS_FOR_TARGET) -S -o$@ $<

%.i: %.ccc $(headers.target) libexec/biting-pear/omnomnom \
    libexec/biting-pear/nomnom
	mkdir -p $(@D)
	$(CXX_FOR_TARGET) -E -x c++ $(CPPFLAGS_FOR_TARGET) \
	    $(CXXFLAGS_FOR_TARGET) -o$@.tmp $<
	$(conf_Host_exec) libexec/biting-pear/omnomnom \
	    "`$(conf_Host_exec) libexec/biting-pear/nomnom <$@.tmp`" \
	    <$@.tmp >$@.2.tmp
	mv $@.2.tmp $@
	rm $@.tmp

libexec/biting-pear/%: libexec/biting-pear/%.cc
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o$@ $< $(LDLIBS)

libexec/biting-pear/omnomnom.cc: libexec/biting-pear/omnomnom.lxx
	mkdir -p $(@D)
	$(LEX) $(LFLAGS) -t -o$@ $< >$@.tmp
	mv $@.tmp $@

.PHONY: test/test-%.passed

.PRECIOUS: config.cache %.i %.cc %.s %.o helper/% $(tests.target) \
    $(utils.host)
