-include config.cache

conf_Srcdir ?= .
include $(conf_Srcdir)/lolwutconf/lolwutconf.mk

bindir = $(conf_Prefix)/bin
datarootdir = $(conf_Prefix)/share
includedir.target = $(conf_Target_prefix)/include

wrap_cxx = bin/innocent-pear-c++
wrap_cxx.staged = $(wrap_cxx) \
    -Xinnocent-pear -prefix=. -Xinnocent-pear -target-prefix=.
config.h.host = include/innocent-pear/host/derp.h
headers.host = \
    include/innocent-pear/bbq.h \
    include/innocent-pear/nowai.h \
    include/innocent-pear/host/lolcat.h \
    include/innocent-pear/host/rly.h \
    include/innocent-pear/host/srsly.h \
    $(config.h.host)
config.h.target = include/innocent-pear/derp.h
headers.target = \
    include/innocent-pear/bbq.h \
    include/innocent-pear/dawg.h \
    include/innocent-pear/kthxbai.h \
    include/innocent-pear/lolwut.h \
    include/innocent-pear/nowai.h \
    include/innocent-pear/omg.h \
    include/innocent-pear/orly.h \
    include/innocent-pear/rofl.h \
    include/innocent-pear/yarly.h \
    include/innocent-pear/yodawg.h \
    $(config.h.target)
tests.target = \
    test/test-kthxbai \
    test/test-kthxbai-p \
    test/test-orly \
    test/test-dawg \
    test/test-dawg-syn \
    test/test-yodawg \
    test/test-yodawg-syn \
    test/test-orly-wut \
    test/test-doge \
    test/test-doge-abs-reloc
utils.host = \
    bin/innocent-pear-c++ \
    bin/innocent-pear-doge \
    share/innocent-pear/calm \
    share/innocent-pear/omnomnom
modules.host = \
    bin/innocent-pear-c++.o \
    bin/innocent-pear-doge.o \
    bin/innocent-pear-dogecoin.o \
    share/innocent-pear/calm.o \
    share/innocent-pear/epic.o \
    share/innocent-pear/keyboard.o \
    share/innocent-pear/nomnom.o \
    share/innocent-pear/omnomnom.o \
    share/innocent-pear/sleepier.o
installables.host = \
    $(utils.host) \
    share/innocent-pear/doge-1.cc \
    share/innocent-pear/doge-2.cc \
    share/innocent-pear/doge-3.cc \
    share/innocent-pear/doge-4.cc \
    share/innocent-pear/doge-8.cc \
    share/innocent-pear/doge-9.cc
RM ?= rm -f

default all: check

.PHONY: default all check install uninstall clean distclean \
    install-host-files install-target-files \
    uninstall-host-files uninstall-target-files

check: $(tests.target:=.passed) $(installables.host)

install: install-host-files install-target-files

install-host-files: $(installables.host)
	install -d $(bindir) $(datarootdir)/innocent-pear
	for u in $^; do \
		if test -x "$$u"; \
		then	m=755; \
		else	m=644; fi; \
		case "$$u" in \
		    bin/*) \
			install -m "$$m" "$$u" $(bindir);; \
		    *)	install -m "$$m" "$$u" $(datarootdir)/innocent-pear;; \
		esac; \
	done

install-target-files: $(headers.target)
	install -d $(includedir.target)/innocent-pear
	install -m 644 $^ $(includedir.target)/innocent-pear

uninstall: uninstall-host-files uninstall-target-files

unnstall-host-files:
	for u in $(installables.host); do \
		case "$$u" in \
		    bin/*) \
			$(RM) $(bindir)/"$$u";; \
		    *)	$(RM) $(datarootdir)/innocent-pear/"$$u";; \
		esac; \
	done

uninstall-target-files:
	$(foreach hdr,$(headers.target), \
	    $(RM) $(includedir.target)/innocent-pear/$(notdir $(hdr)) &&) \
	    true
	-rmdir -p $(bindir) $(includedir.target)/innocent-pear \
	    $(datarootdir)/innocent-pear

clean:
	find . -name '*.[ios]' -o -name '*~' -o -name '*.ii' | \
	    xargs $(RM) $(config.h.host) $(config.h.target) \
		lex.backup share/innocent-pear/omnomnom.cc \
		$(tests.target) $(utils.host) lolwutconf.*
ifeq "$(conf_Separate_build_dir)" "yes"
	-rmdir helper test util
endif

distclean: clean
	$(RM) config.cache
ifeq "$(conf_Separate_build_dir)" "yes"
	$(RM) GNUmakefile
endif

config.cache:
	@echo '*'
	@echo '* run `$(conf_Srcdir)/configure --help'\' \
	      'to see how to build this project!'
	@echo '*'
	@exit 1

$(config.h.host) $(config.h.target): config.cache
	mkdir -p $(@D)
	echo "/****** AUTOMATICALLY GENERATED `date` ******/" >$@.tmp
	if test '$(config.h.host)' = '$@'; \
		then echo '#include <cstdlib>' >>$@.tmp; fi
	if test '$(conf_Have_cxx_typ_std_0uint64_1t),$@' = \
	    'yes,$(config.h.host)'; then \
		echo '#include <cinttypes>' >>$@.tmp; \
	elif test '$(conf_Have_cxxt_typ_std_0uint64_1t),$@' = \
	    'yes,$(config.h.target)'; then \
		echo '#include <cinttypes>' >>$@.tmp; \
	elif test '$(config.h.target)' = '$@'; then \
		echo '#include <inttypes.h>' >>$@.tmp; \
	fi
	if test '$(conf_Have_cxxt_typ_std_0uintptr_1t),$@' = \
	    'yes,$(config.h.target)'; then \
		echo '#include <cinttypes>' >>$@.tmp; \
	elif test '$(config.h.target)' = '$@'; then \
		echo '#include <inttypes.h>' >>$@.tmp; \
	fi
	if test \( \
	    yes = '$(conf_Have_cxx_func_std_0mbrtoc16)' -o \
	    yes = '$(conf_Have_cxx_func_std_0mbrtoc32)' \) -a \
	    '$(config.h.host)' = '$@'; then \
		echo '#include <cuchar>' >>$@.tmp; \
	fi
	if test yes = '$(conf_Have_cxx_func_std_0mbrtowc)' -a \
	    '$(config.h.host)' = '$@'; then \
		echo '#include <cwchar>' >>$@.tmp; \
	fi
	if test \( \
	    yes = '$(conf_Have_cxx_func__0mbrtoc16)' -o \
	    yes = '$(conf_Have_cxx_func__0mbrtoc32)' \) -a \
	    '$(config.h.host)' = '$@'; then \
		echo '#include <uchar.h>' >>$@.tmp; \
	fi
	if test yes = '$(conf_Have_cxx_func__0mbrtowc)' -a \
	    '$(config.h.host)' = '$@'; then \
		echo '#include <wchar.h>' >>$@.tmp; \
	fi
	if test '$(config.h.host)' = '$@'; then \
		if test yes = '$(conf_Have_cxx_typ_std_0mt19937_164)'; then \
			echo '#include <random>'; \
		else \
			echo '#include <boost/random/mersenne_twister.hpp>'; \
		fi >>$@.tmp; \
	fi
	echo 'namespace innocent_pear { namespace impl {' >>$@.tmp
	if test '$(conf_Have_cxx_typ_std_0uint64_1t),$@' = \
	    'yes,$(config.h.host)'; then \
		echo 'using std::uint64_t;' >>$@.tmp; \
	elif test '$(conf_Have_cxxt_typ_std_0uint64_1t),$@' = \
	    'yes,$(config.h.target)'; then \
		echo 'using std::uint64_t;' >>$@.tmp; \
	else \
		echo 'using ::uint64_t;' >>$@.tmp; \
	fi
	if test '$(conf_Have_cxxt_typ_std_0uintptr_1t),$@' = \
	    'yes,$(config.h.target)'; then \
		echo 'using std::uintptr_t;' >>$@.tmp; \
	elif test '$(config.h.target)' = '$@'; then \
		echo 'using ::uintptr_t;' >>$@.tmp; \
	fi
	if test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func_std_0mbrtoc16),$@'; then \
		echo 'using std::mbrtoc16;' >>$@.tmp; \
	elif test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func__0mbrtoc16),$@'; then \
		echo 'using ::mbrtoc16;' >>$@.tmp; \
	fi
	if test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func_std_0mbrtoc32),$@'; then \
		echo 'using std::mbrtoc32;' >>$@.tmp; \
	elif test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func__0mbrtoc32),$@'; then \
		echo 'using ::mbrtoc32;' >>$@.tmp; \
	fi
	if test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func_std_0mbrtowc),$@'; then \
		echo 'using std::mbrtowc;' >>$@.tmp; \
	elif test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func__0mbrtowc),$@'; then \
		echo 'using ::mbrtowc;' >>$@.tmp; \
	fi
	if test '$(config.h.host)' = '$@'; then \
		if test yes = '$(conf_Have_cxx_typ_std_0mt19937_164)'; then \
			echo 'using std::mt19937_64;'; \
		else \
			echo 'using boost::mt19937_64;'; \
		fi >>$@.tmp; \
	fi
	if test 'yes,$(config.h.host)' = \
	    '$(conf_Have_cxx_func__0secure_1getenv),$@'; then \
		echo 'inline char *getenv(const char *name)' >>$@.tmp; \
		echo '{ return ::secure_getenv(name); }' >>$@.tmp; \
	elif test '$(config.h.host)' = '$@'; then \
		echo 'using std::getenv;' >>$@.tmp; \
	fi
	echo '} }' >>$@.tmp
ifeq "char16_t" "$(conf_Typ_wchar_cxx)"
	if test x'$@' = x'$(config.h.host)'; then \
		echo "#define innocent_pear_HOST_WCHAR_IS_CHAR16 1"; \
		echo "#undef innocent_pear_HOST_WCHAR_IS_CHAR32"; \
	fi >>$@.tmp
else ifeq "char32_t" "$(conf_Typ_wchar_cxx)"
	if test x'$@' = x'$(config.h.host)'; then \
		echo "#undef innocent_pear_HOST_WCHAR_IS_CHAR16"; \
		echo "#define innocent_pear_HOST_WCHAR_IS_CHAR32 1"; \
	fi >>$@.tmp
else
	if test x'$@' = x'$(config.h.host)'; then \
		echo "#undef innocent_pear_HOST_WCHAR_IS_CHAR16"; \
		echo "#undef innocent_pear_HOST_WCHAR_IS_CHAR32"; \
	fi >>$@.tmp
endif
ifeq "char16_t" "$(conf_Typ_wchar_cxxt)"
	if test x'$@' = x'$(config.h.host)'; then \
		echo "#define innocent_pear_TARGET_WCHAR_IS_CHAR16 1"; \
		echo "#undef innocent_pear_TARGET_WCHAR_IS_CHAR32"; \
	fi >>$@.tmp
else ifeq "char32_t" "$(conf_Typ_wchar_cxxt)"
	if test x'$@' = x'$(config.h.host)'; then \
		echo "#undef innocent_pear_TARGET_WCHAR_IS_CHAR16"; \
		echo "#define innocent_pear_TARGET_WCHAR_IS_CHAR32 1"; \
	fi >>$@.tmp
else
	if test x'$@' = x'$(config.h.host)'; then \
		echo "#undef innocent_pear_TARGET_WCHAR_IS_CHAR16"; \
		echo "#undef innocent_pear_TARGET_WCHAR_IS_CHAR32"; \
	fi >>$@.tmp
endif
	if test '$(conf_Have_cxx_decltype),$@' = 'yes,$(config.h.host)'; then\
		echo '#define innocent_pear_decltype decltype' >>$@.tmp; \
	elif test '$(conf_Have_cxxt_decltype),$@' = \
	    'yes,$(config.h.target)'; then \
		echo '#define innocent_pear_decltype decltype' >>$@.tmp; \
	else \
		echo '#define innocent_pear_decltype __typeof' >>$@.tmp; \
	fi
	if test '$(conf_Have_asm_goto_cxx),$@' = 'yes,$(config.h.host)' -o \
		'$(conf_Have_asm_goto_cxxt),$@' = 'yes,$(config.h.target)'; \
	then \
		echo '#define innocent_pear_HAVE_ASM_GOTO 1' >>$@.tmp; \
	else \
		echo '#undef innocent_pear_HAVE_ASM_GOTO' >>$@.tmp; \
	fi
	if test '$(conf_Have_ctor_priority_cxxt),$@' = \
	    'yes,$(config.h.target)'; then \
		echo '#define innocent_pear_HAVE_CTOR_PRIORITY 1' >>$@.tmp; \
	else \
		echo '#undef innocent_pear_HAVE_CTOR_PRIORITY' >>$@.tmp; \
	fi
	set -e; \
	if test '$(config.h.target)' = '$@'; then \
		if test '$(conf_Have_cxxt_func__0ptrace)' = yes; then \
			echo '#define innocent_pear_HAVE_FUNC_PTRACE 1'; \
		else \
			echo '#undef innocent_pear_HAVE_FUNC_PTRACE'; \
		fi; \
		if test '$(conf_Have_cxxt_impld_func__0ptrace)' = yes; then \
			echo '#define innocent_pear_HAVE_IMPLD_FUNC_PTRACE 1';\
		else \
			echo '#undef innocent_pear_HAVE_IMPLD_FUNC_PTRACE'; \
		fi; \
		if test '$(conf_Have_cxxt_func__0tcflow)' = yes; then \
			echo '#define innocent_pear_HAVE_FUNC_TCFLOW 1'; \
		else \
			echo '#undef innocent_pear_HAVE_FUNC_TCFLOW'; \
		fi; \
		$(foreach c,PT_TRACE_ME PT_READ_I PT_READ_D PT_READ_U, \
			if test '$(conf_Have_cxxt_const_$(subst _,_1,$c))' = \
			    yes; then \
				echo \
				 '#define innocent_pear_HAVE_CONST_$c 1';\
			else	echo \
				 '#undef innocent_pear_HAVE_CONST_$c'; \
			fi; ) \
		$(foreach c,TCOOFF TCOON TCXONC TIOCSTOP TIOCSTART, \
			if test '$(conf_Have_cxxt_const_$(subst _,_1,$c))' = \
			    yes; then \
				echo \
				 '#define innocent_pear_HAVE_CONST_$c 1';\
				echo \
				 '#define innocent_pear_VAL_CONST_$c' \
				    '$(conf_Val_cxxt_const_$(subst _,_1,$c))';\
			else	echo \
				 '#undef innocent_pear_HAVE_CONST_$c'; \
			fi; ) \
	fi >>$@.tmp
	set -e; \
	if test '$(config.h.host)' = '$@'; then \
		if test '$(conf_Have_cxx_func__0fdatasync)' = yes; then \
			echo '#define innocent_pear_HAVE_FUNC_FDATASYNC 1'; \
		else \
			echo '#undef innocent_pear_HAVE_FUNC_FDATASYNC'; \
		fi; \
		if test '$(conf_Have_cxxt_opt_fno_integrated_as)' = yes; then \
			echo '#define' \
			  'innocent_pear_CXX_FOR_TARGET_DECOUPLE_AS 1'; \
		else	echo '#undef' \
			  'innocent_pear_CXX_FOR_TARGET_DECOUPLE_AS'; \
		fi; \
		if test '$(conf_Have_cxxt_opt_wrapper)' = yes; then \
			echo '#define' \
			  'innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER 1'; \
		else	echo '#undef' \
			  'innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER'; \
		fi; \
		echo "#define innocent_pear_CXXFLAGS_FOR_TARGET \\" >>$@.tmp; \
		set -- $(CXXFLAGS_FOR_TARGET); \
		if test 0 != $$#; then \
			echo "$$1" | \
			    sed 's/["\\]/\\&/g; s/^/"/; s/$$/"\\/'; \
			shift; \
			for arg; do \
				echo "$$arg" | \
				    sed 's/["\\]/\\&/g; s/^/,"/; s/$$/"\\/';\
			done; \
		fi; \
		echo '/* done */'; \
	fi >>$@.tmp
	mv $@.tmp $@

test/test-%.passed: test/test-% test/test-%.good
	@echo "* running test $<" >&2
	@LANG=en_US.UTF-8 $(conf_Target_exec) ./$< >$(@:.passed=.1.tmp) \
	    2>$(@:.passed=.2.tmp) ||\
	    (echo "* $< exited with error: $$?" >&2 && \
	     $(RM) $(@:.passed=.1.tmp) $(@:.passed=.2.tmp) && \
	     exit 1)
	@LANG=en_US.UTF-8 diff -U2 /dev/null $(@:.passed=.2.tmp) || \
	    (echo "* $< produced output on stderr" >&2 && \
	     $(RM) $(@:.passed=.1.tmp) $(@:.passed=.2.tmp) && \
	     exit 1)
	@LANG=en_US.UTF-8 diff -U2 $<.good $(@:.passed=.1.tmp) || \
	    (echo "* $<'s expected output and actual output differ" >&2 && \
	     $(RM) $(@:.passed=.1.tmp) $(@:.passed=.2.tmp) && \
	     exit 1)
	@echo "* $< passed" >&2
	@$(RM) $(@:.passed=.1.tmp) $(@:.passed=.2.tmp)

test/test-%: test/test-%.o
	$(conf_Host_exec) $(wrap_cxx.staged) $(CXXFLAGS_FOR_TARGET) \
	    $(LDFLAGS_FOR_TARGET) -o$@ $^ $(LDLIBS_FOR_TARGET)

test/test-%.o: test/test-%.cc

test/test-orly-wut \
test/test-orly-wut.o \
test/test-orly-wut.s : state = 0x293c42fc93032e55

test/test-orly-wut.o \
test/test-orly-wut.s : CXXFLAGS_FOR_TARGET += -DSTATE=$(state)

test/test-orly-wut: test/test-orly-wut.o test/test-orly-wut.ld \
    bin/innocent-pear-doge
	$(conf_Host_exec) $(wrap_cxx.staged) $(CXXFLAGS_FOR_TARGET) \
	    $(LDFLAGS_FOR_TARGET) -o$@.tmp $(filter %.o %.ld,$^) \
	    $(LDLIBS_FOR_TARGET)
	bin/innocent-pear-doge $@.tmp $@ __doge_start __doge_end $(state)
	$(RM) $@.tmp

test/test-doge \
test/test-doge.o \
test/test-doge.s : CXXFLAGS_FOR_TARGET += -Xinnocent-pear -doge -v

define preproc_for_host
	mkdir -p $(@D)
	$(CXX) -E -x c++ $(CPPFLAGS) $(CXXFLAGS) -o$@.tmp $<
	$(conf_Host_exec) share/innocent-pear/omnomnom <$@.tmp >$@.2.tmp
	mv $@.2.tmp $@
	$(RM) $@.tmp
endef

bin/innocent-pear-c++: bin/innocent-pear-c++.o share/innocent-pear/epic.o \
    share/innocent-pear/nomnom.o share/innocent-pear/keyboard.o \
    share/innocent-pear/sleepier.o

bin/innocent-pear-doge: bin/innocent-pear-doge.o \
    share/innocent-pear/epic.o share/innocent-pear/sleepier.o

bin/innocent-pear-dogecoin: bin/innocent-pear-dogecoin.o \
    share/innocent-pear/epic.o share/innocent-pear/sleepier.o

share/innocent-pear/calm: share/innocent-pear/calm.o \
    share/innocent-pear/epic.o share/innocent-pear/nomnom.o \
    share/innocent-pear/keyboard.o share/innocent-pear/sleepier.o

$(foreach m,$(modules.host), \
    $(eval $m: $(m:.o=.ii)))

bin/%.ii share/innocent-pear/%.ii : \
    CPPFLAGS += -Dinnocent_pear_HOST_PREFIX=\"$(conf_Prefix)\" \
		-Dinnocent_pear_TARGET_PREFIX=\"$(conf_Target_prefix)\" \
		-Dinnocent_pear_CXX_FOR_TARGET=\"$(CXX_FOR_TARGET)\" \
		$(if $(filter yes,$(conf_Dyn_ld_cxxt)), \
		    -Dinnocent_pear_DYN_LD_CXX_TARGET, \
		    -Uinnocent_pear_DYN_LD_CXX_TARGET)

bin/%: bin/%.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^ $(LDLIBS)

# for debugging
ifeq "$(conf_Have_cxx_opt_fno_integrated_as)" "yes"
bin/%.s : CXXFLAGS += -fno-integrated-as
endif
bin/%.s: bin/%.ii
	$(CXX) $(CXXFLAGS) -S -o$@ $<

bin/%.o: bin/%.ii
	$(CXX) $(CXXFLAGS) -c -o$@ $<

bin/%.ii: bin/%.cc $(headers.host) $(headers.target) \
    share/innocent-pear/calm share/innocent-pear/omnomnom
	$(preproc_for_host)

share/innocent-pear/%: share/innocent-pear/%.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^ $(LDLIBS)

share/innocent-pear/%.o: share/innocent-pear/%.ii
	$(CXX) $(CXXFLAGS) -c -o$@ $<

# for debugging
ifeq "$(conf_Have_cxx_opt_fno_integrated_as)" "yes"
share/innocent-pear/%.s : CXXFLAGS += -fno-integrated-as
endif
share/innocent-pear/%.s: share/innocent-pear/%.ii
	$(CXX) $(CXXFLAGS) -S -o$@ $<

share/innocent-pear/%.ii: share/innocent-pear/%.cc $(headers.host) \
    $(headers.target) share/innocent-pear/omnomnom
	$(preproc_for_host)

share/innocent-pear/omnomnom: share/innocent-pear/omnomnom.cc \
    $(config.h.host)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o$@ $<

%.o: %.cc $(headers.target) $(installables.host)
	mkdir -p $(@D)
	$(conf_Host_exec) $(wrap_cxx.staged) $(CXXFLAGS_FOR_TARGET) \
	    -c -o$@ $<

# for debugging
%.s: %.cc $(headers.target) $(installables.host)
	mkdir -p $(@D)
	$(conf_Host_exec) $(wrap_cxx.staged) $(CXXFLAGS_FOR_TARGET) \
	    -S -o$@ $<

share/innocent-pear/%: share/innocent-pear/%.cc
	mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o$@ $< $(LDLIBS)

share/innocent-pear/omnomnom.cc: share/innocent-pear/omnomnom.lxx
	mkdir -p $(@D)
	$(LEX) $(LFLAGS) -t -o$@ $< >$@.tmp
	mv $@.tmp $@

.PHONY: test/test-%.passed

.PRECIOUS: config.cache %.ii %.cc %.s %.o bin/%.o share/innocent-pear/%.o \
    helper/% $(tests.target) $(installables.host)
