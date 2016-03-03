-include config.cache

conf_Srcdir ?= .
include $(conf_Srcdir)/lolwutconf/lolwutconf.mk

bindir = $(conf_Prefix)/bin
datarootdir = $(conf_Prefix)/share
includedir.target = $(conf_Target_prefix)/include

wrap_cxx = bin/biting-pear-c++
wrap_cxx.staged = $(wrap_cxx) \
    -Xbiting-pear -prefix=. -Xbiting-pear -target-prefix=.
config.h.host = include/biting-pear/host/derp.h
headers.host = \
    include/biting-pear/bbq.h \
    include/biting-pear/nowai.h \
    include/biting-pear/host/lolcat.h \
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
    test/test-kthxbai \
    test/test-kthxbai-p \
    test/test-orly
ifeq "$(conf_Have_cxxt_var_tpls)" "yes"
tests.target += \
    test/test-dawg \
    test/test-dawg-syn \
    test/test-yodawg \
    test/test-yodawg-syn
endif
utils.host = \
    bin/biting-pear-c++ \
    share/biting-pear/calm \
    share/biting-pear/omnomnom
ifeq "$(conf_Have_cxx_typ_struct_bfd)" "yes"
ifeq "$(conf_Have_cxx_lib_bfd)" "yes"
ifeq "$(conf_Have_cxx_var_tpls)" "yes"
utils.host += \
    bin/biting-pear-doge
tests.target += \
    test/test-orly-wut
endif
endif
endif
installables.host = \
    $(utils.host) \
    share/biting-pear/calm.spec

default all: check

check: $(tests.target:=.passed) $(installables.host)

install: install-host-files install-target-files

install-host-files: $(installables.host)
	install -d $(bindir) $(datarootdir)/biting-pear
	for u in $^; do \
		if test -x "$$u"; \
		then	m=755; \
		else	m=644; fi; \
		case "$$u" in \
		    bin/*) \
			install -m "$$m" "$$u" $(bindir);; \
		    *)	install -m "$$m" "$$u" $(datarootdir)/biting-pear;; \
		esac; \
	done

install-target-files: $(headers.target)
	install -d $(includedir.target)/biting-pear
	install -m 644 $^ $(includedir.target)/biting-pear

uninstall:
	$(foreach hdr,$(headers.target), \
	    rm -f $(includedir.target)/biting-pear/$(notdir $(hdr)) &&) \
	    true
	-rmdir -p $(bindir) $(includedir.target)/biting-pear \
	    $(datarootdir)/biting-pear

clean:
	find . -name '*.[ios]' -o -name '*~' -o -name '*.ii' | \
	    xargs rm -f $(config.h.host) $(config.h.target) \
		lex.backup share/biting-pear/omnomnom.cc \
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

$(config.h.host) $(config.h.target): config.cache
	mkdir -p $(@D)
	echo "/****** AUTOMATICALLY GENERATED `date` ******/" >$@.tmp
	if test '$(config.h.host)' = '$@'; \
		then echo '#include <cstdlib>' >>$@.tmp; fi
	if test '$(conf_Have_cxx_typ_std__uint_least64_t),$@' = \
	    'yes,$(config.h.host)'; then \
		echo '#include <cinttypes>' >>$@.tmp; \
	elif test '$(conf_Have_cxxt_typ_std__uint_least64_t),$@' = \
	    'yes,$(config.h.target)'; then \
		echo '#include <cinttypes>' >>$@.tmp; \
	else \
		echo '#include <inttypes.h>' >>$@.tmp; \
	fi
	if test \( \
	    yes = '$(conf_Have_cxx_func_std__mbrtoc16)' -o \
	    yes = '$(conf_Have_cxx_func_std__mbrtoc32)' \) -a \
	    '$(config.h.host)' = '$@'; then \
		echo '#include <cuchar>' >>$@.tmp; \
	fi
	if test \( \
	    yes = '$(conf_Have_cxx_func___mbrtoc16)' -o \
	    yes = '$(conf_Have_cxx_func___mbrtoc32)' \) -a \
	    '$(config.h.host)' = '$@'; then \
		echo '#include <uchar.h>' >>$@.tmp; \
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
	if test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func_std__mbrtoc16),$@'; then \
		echo 'using std::mbrtoc16;' >>$@.tmp; \
	elif test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func___mbrtoc16),$@'; then \
		echo 'using ::mbrtoc16;' >>$@.tmp; \
	fi
	if test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func_std__mbrtoc32),$@'; then \
		echo 'using std::mbrtoc32;' >>$@.tmp; \
	elif test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func___mbrtoc32),$@'; then \
		echo 'using ::mbrtoc32;' >>$@.tmp; \
	fi
	if test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func___secure_getenv),$@'; then \
		echo 'inline char *getenv(const char *name)' >>$@.tmp; \
		echo '{ return ::secure_getenv(name); }' >>$@.tmp; \
	elif test '$(config.h.host)' = '$@'; then \
		echo 'using std::getenv;' >>$@.tmp; \
	fi
	echo '} }' >>$@.tmp
ifeq "char16_t" "$(conf_Typ_wchar_cxxt)"
	if test x'$@' = x'$(config.h.host)'; then \
		echo "#define biting_pear_TARGET_WCHAR_IS_CHAR16 1"; \
		echo "#undef biting_pear_TARGET_WCHAR_IS_CHAR32"; \
	fi >>$@.tmp
else ifeq "char32_t" "$(conf_Typ_wchar_cxxt)"
	if test x'$@' = x'$(config.h.host)'; then \
		echo "#undef biting_pear_TARGET_WCHAR_IS_CHAR16"; \
		echo "#define biting_pear_TARGET_WCHAR_IS_CHAR32 1"; \
	fi >>$@.tmp
else
	if test x'$@' = x'$(config.h.host)'; then \
		echo "#undef biting_pear_TARGET_WCHAR_IS_CHAR16"; \
		echo "#undef biting_pear_TARGET_WCHAR_IS_CHAR32"; \
	fi >>$@.tmp
endif
	if test '$(conf_Have_cxx_var_tpls),$@' = 'yes,$(config.h.host)'; then\
		echo '#define biting_pear_HAVE_CXX_VAR_TPLS 1' >>$@.tmp; \
	elif test '$(conf_Have_cxxt_var_tpls),$@' = \
	    'yes,$(config.h.target)'; then \
		echo '#define biting_pear_HAVE_CXX_VAR_TPLS 1' >>$@.tmp; \
	else \
		echo '#undef biting_pear_HAVE_CXX_VAR_TPLS' >>$@.tmp; \
	fi
	if test '$(conf_Have_cxx_decltype),$@' = 'yes,$(config.h.host)'; then\
		echo '#define biting_pear_decltype decltype' >>$@.tmp; \
	elif test '$(conf_Have_cxxt_decltype),$@' = \
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
	$(conf_Host_exec) $(CXX_FOR_TARGET) $(CXXFLAGS_FOR_TARGET) \
	    $(LDFLAGS_FOR_TARGET) -o$@ $^ $(LDLIBS_FOR_TARGET)

test/test-%.o: test/test-%.ccc

test/test-orly-wut test/test-orly-wut.o : state = 0x293c42fc93032e55

test/test-orly-wut.o : CXXFLAGS_FOR_TARGET += -DSTATE=$(state)

test/test-orly-wut: test/test-orly-wut.o test/test-orly-wut.ld \
    bin/biting-pear-doge
	$(conf_Host_exec) $(CXX_FOR_TARGET) $(CXXFLAGS_FOR_TARGET) \
	    $(LDFLAGS_FOR_TARGET) -o$@.tmp $(filter %.o %.ld,$^) \
	    $(LDLIBS_FOR_TARGET)
	bin/biting-pear-doge $@.tmp $@ __doge_start __doge_end $(state)
	rm $@.tmp

define preproc_for_host
	mkdir -p $(@D)
	$(CXX) -E -x c++ $(CPPFLAGS) $(CXXFLAGS) -o$@.tmp $<
	$(conf_Host_exec) share/biting-pear/omnomnom <$@.tmp >$@.2.tmp
	mv $@.2.tmp $@
	rm $@.tmp
endef

bin/biting-pear-c++: bin/biting-pear-c++.o share/biting-pear/epic.o

bin/biting-pear-c++.o: bin/biting-pear-c++.ii

bin/biting-pear-doge: bin/biting-pear-doge.o share/biting-pear/epic.o

bin/biting-pear-doge.o: bin/biting-pear-doge.ii

share/biting-pear/calm: share/biting-pear/calm.o share/biting-pear/epic.o \
    share/biting-pear/nomnom.o

share/biting-pear/calm.o: share/biting-pear/calm.ii

share/biting-pear/epic.o: share/biting-pear/epic.ii

bin/%.ii share/biting-pear/%.ii : \
    CPPFLAGS += -Dbiting_pear_HOST_PREFIX=\"$(conf_Prefix)\" \
		-Dbiting_pear_TARGET_PREFIX=\"$(conf_Target_prefix)\" \
		-Dbiting_pear_CXX_FOR_TARGET=\"$(CXX_FOR_TARGET)\"

bin/%: bin/%.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^ $(LDLIBS)

bin/%.o: bin/%.ii
	$(CXX) $(CXXFLAGS) -c -o$@ $<

bin/%.ii: bin/%.ccc $(headers.host) $(headers.target) \
    share/biting-pear/calm share/biting-pear/omnomnom
	$(preproc_for_host)

share/biting-pear/%: share/biting-pear/%.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^ $(LDLIBS)

share/biting-pear/%.o: share/biting-pear/%.ii
	$(CXX) $(CXXFLAGS) -c -o$@ $<

# for debugging
share/biting-pear/%.s: share/biting-pear/%.ii
	$(CXX) $(CXXFLAGS) -S -o$@ $<

share/biting-pear/%.ii: share/biting-pear/%.ccc $(headers.host) \
    $(headers.target) share/biting-pear/omnomnom
	$(preproc_for_host)

share/biting-pear/omnomnom.o: share/biting-pear/omnomnom.cc \
    $(config.h.host)

%.o: %.ccc $(headers.target) $(wrap_cxx) share/biting-pear/omnomnom \
    share/biting-pear/calm share/biting-pear/calm.spec
	mkdir -p $(@D)
	$(conf_Host_exec) $(wrap_cxx.staged) $(CXXFLAGS_FOR_TARGET) \
	    -c -o$@ $<

# for debugging
%.s: %.ccc $(headers.target) $(wrap_cxx) share/biting-pear/omnomnom \
    share/biting-pear/calm share/biting-pear/calm.spec
	mkdir -p $(@D)
	$(conf_Host_exec) $(wrap_cxx.staged) $(CXXFLAGS_FOR_TARGET) \
	    -S -o$@ $<

share/biting-pear/%: share/biting-pear/%.cc
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o$@ $< $(LDLIBS)

share/biting-pear/omnomnom.cc: share/biting-pear/omnomnom.lxx
	mkdir -p $(@D)
	$(LEX) $(LFLAGS) -t -o$@ $< >$@.tmp
	mv $@.tmp $@

.PHONY: test/test-%.passed

.PRECIOUS: config.cache %.ii %.cc %.s %.o bin/%.o share/biting-pear/%.o \
    helper/% $(tests.target) $(installables.host)
