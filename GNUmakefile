include config.cache

conf_Srcdir ?= .
conf_Lolwutconf_dir ?= $(conf_Srcdir)/lolwutconf
include $(conf_Lolwutconf_dir)/lolwutconf.mk

bindir = $(conf_Prefix)/bin
datarootdir = $(conf_Prefix)/share
includedir.target = $(conf_Target_prefix)/include
#
# The header files in KeccakCodePackage are scattered across the directory
# tree.  To work around this, I arrange to copy all the header files to a
# single (new) directory, and do a single `-I' to point to them.
#
# See the definition of $(headers.host), the `clean' rule, and the rules
# for the `infra/keccak/' files below.  Also note that we compile the .c
# source files for Keccak as C++.
#
CPPFLAGS += -Iinfra/keccak

prefix_opts = \
    -Xinnocent-pear -prefix='$(conf_Srcdir)' \
    -Xinnocent-pear -exec-prefix=. \
    -Xinnocent-pear -target-prefix='$(conf_Srcdir)' \
    -Xinnocent-pear -target-exec-prefix=.
wrap_cxx = bin/innocent-pear-c++
wrap_cxx.staged = $(wrap_cxx) $(prefix_opts)
wrap_cc = bin/innocent-pear-cc
wrap_cc.staged = $(wrap_cc) $(prefix_opts)
CXXFLAGS_FOR_TARGET.test = $(CXXFLAGS_FOR_TARGET)
CFLAGS_FOR_TARGET.test = $(CFLAGS_FOR_TARGET)
config.h.host = include/innocent-pear/host/derp.h
headers.keccak.host = \
    infra/keccak/KeccakPRG.h \
    infra/keccak/KeccakPRG.inc \
    infra/keccak/align.h \
    infra/keccak/brg_endian.h \
    infra/keccak/KeccakDuplex.h \
    infra/keccak/KeccakDuplex.inc \
    infra/keccak/KeccakP-1600-SnP.h
headers.host = \
    bin/innocent-pear-front-end.tcc \
    include/innocent-pear/bbq.h \
    include/innocent-pear/nowai.h \
    include/innocent-pear/host/lolcat.h \
    include/innocent-pear/host/moar.h \
    include/innocent-pear/host/rly.h \
    include/innocent-pear/host/srsly.h \
    $(headers.keccak.host) \
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
    include/innocent-pear/teh.h \
    include/innocent-pear/tfw.h \
    include/innocent-pear/unpossible.h \
    include/innocent-pear/yarly.h \
    include/innocent-pear/yodawg.h \
    $(config.h.target)
tests.target = \
    test/test-kthxbai \
    test/test-kthxbai-p \
    test/test-omg-wheee.debug \
    test/test-omg-wheee \
    test/test-omg-special.debug \
    test/test-omg-special \
    test/test-orly-1 \
    test/test-orly-2 \
    test/test-orly-3 \
    test/test-dawg \
    test/test-dawg-syn \
    test/test-yodawg \
    test/test-yodawg-syn \
    test/test-orly-wut \
    test/test-doge.debug \
    test/test-doge \
    test/test-doge-with-dawg \
    test/test-doge-abs-reloc \
    test/test-doge-eh \
    test/test-doge-with-c
utils.host = \
    bin/innocent-pear-c++ \
    bin/innocent-pear-cc \
    bin/innocent-pear-doge \
    bin/innocent-pear-dogecoin \
    share/innocent-pear/calm \
    share/innocent-pear/omnomnom
modules.host = \
    bin/innocent-pear-c++.o \
    bin/innocent-pear-cc.o \
    bin/innocent-pear-doge.o \
    bin/innocent-pear-dogecoin.o \
    share/innocent-pear/calm.o \
    share/innocent-pear/epic.o \
    share/innocent-pear/keyboard.o \
    share/innocent-pear/lolrus.o \
    share/innocent-pear/moar.o \
    share/innocent-pear/omnomnom.o \
    share/innocent-pear/sleepier.o \
    infra/keccak/KeccakPRG.o \
    infra/keccak/KeccakDuplex.o \
    infra/keccak/KeccakP-1600-reference.o
installables.host = \
    $(utils.host) \
    share/innocent-pear/doge-i.h \
    share/innocent-pear/doge-01.cc \
    share/innocent-pear/doge-02.cc \
    share/innocent-pear/doge-03.cc \
    share/innocent-pear/doge-04.cc \
    share/innocent-pear/doge-05.cc \
    share/innocent-pear/doge-06.cc \
    share/innocent-pear/doge-07.cc \
    share/innocent-pear/doge-45.cc \
    share/innocent-pear/doge-98.cc \
    share/innocent-pear/doge-99.cc \
    share/innocent-pear/doge-i.ld \
    share/innocent-pear/doge-n.ld
installables.target = \
    $(headers.target)
ifeq "yes" "$(conf_Have_appb_wipe)"
    RM = '$(abspath $(conf_Srcdir)/infra/wipe-wrapper.sh)'
else
    RM ?= rm -f
endif

default all: $(installables.host) $(installables.target)

.PHONY: default all check install uninstall clean distclean \
    install-host-files install-target-files \
    uninstall-host-files uninstall-target-files

check: all $(tests.target:=.passed)

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

install-target-files: $(installables.target)
	install -d $(includedir.target)/innocent-pear
	install -m 644 $(headers.target) $(includedir.target)/innocent-pear

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
	find . -name '*.[ios]' -a \! -path './KeccakCodePackage/*' \
	    -o -name '*~' -o -name '*.ii' \
	    -o -name '*.pear.t.??????' | \
	    xargs $(RM) -r $(config.h.host) $(config.h.target) \
		lex.backup share/innocent-pear/omnomnom.cc \
		$(tests.target) $(utils.host) infra/keccak lolwutconf.*
ifeq "$(conf_Separate_build_dir)" "yes"
	-$(RM) -r test
endif

distclean: clean
	$(RM) config.cache
ifeq "$(conf_Separate_build_dir)" "yes"
	-$(RM) GNUmakefile
endif
	test -e KeccakCodePackage/.git || $(RM) -r KeccakCodePackage
	test -e lolwutconf/.git || $(RM) -r lolwutconf

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
	set -e; \
	$(foreach sz, 64 32 16 8, \
		if test '$(conf_Have_cxx_typ_std_0uint_1least$(sz)_1t),$@' = \
		    'yes,$(config.h.host)'; then \
			echo '#include <cinttypes>' >>$@.tmp; \
		elif test '$(conf_Have_cxxt_typ_std_0uint_1least$(sz)_1t),$@' \
		    = 'yes,$(config.h.target)'; then \
			echo '#include <cinttypes>' >>$@.tmp; \
		elif test '$(config.h.target)' = '$@'; then \
			echo '#include <inttypes.h>' >>$@.tmp; \
		fi; ) true
	if test '$(conf_Have_cxxt_typ_std_0intptr_1t),$@' = \
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
	echo 'namespace innocent_pear { namespace impl {' >>$@.tmp
	set -e; \
	$(foreach sz, 64 32 16 8, \
		if test '$(conf_Have_cxx_typ_std_0uint_1least$(sz)_1t),$@' = \
		    'yes,$(config.h.host)'; then \
			echo 'using std::uint_least$(sz)_t;' >>$@.tmp; \
		elif test '$(conf_Have_cxxt_typ_std_0uint_1least$(sz)_1t),$@' \
		    = 'yes,$(config.h.target)'; then \
			echo 'using std::uint_least$(sz)_t;' >>$@.tmp; \
		else \
			echo 'using ::uint_least$(sz)_t;' >>$@.tmp; \
		fi; ) true
	if test '$(conf_Have_cxxt_typ_std_0intptr_1t),$@' = \
	    'yes,$(config.h.target)'; then \
		echo 'using std::intptr_t;' >>$@.tmp; \
	elif test '$(config.h.target)' = '$@'; then \
		echo 'using ::intptr_t;' >>$@.tmp; \
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
	if test yes = '$(conf_Have_cxxt_const__2ELF_2)' -a yes = \
	    '$(conf_Have_cxxt_func__0_2pthread_1initialize_1minimal)'; \
	then \
		echo '#define innocent_pear_FIX_ELF_IFUNC 1'; \
	else \
		echo '#undef innocent_pear_FIX_ELF_IFUNC'; \
	fi >>$@.tmp
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
ifeq "little-endian" "$(conf_Endianness_cxxt)"
	set -e; \
	if test '$(config.h.target)' = '$@'; \
		then echo '#define innocent_pear_ENDIANNESS 1234' >>$@.tmp; fi
else ifeq "big-endian" "$(conf_Endianness_cxxt)"
	set -e; \
	if test '$(config.h.target)' = '$@'; \
		then echo '#define innocent_pear_ENDIANNESS 4321' >>$@.tmp; fi
else
	set -e; \
	if test '$(config.h.target)' = '$@'; \
		then echo '#undef innocent_pear_ENDIANNESS' >>$@.tmp; fi
endif
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
		if test '$(conf_Have_cxxt_func__0prctl)' = yes; then \
			echo '#define innocent_pear_HAVE_FUNC_PRCTL 1'; \
		else \
			echo '#undef innocent_pear_HAVE_FUNC_PRCTL'; \
		fi; \
		if test '$(conf_Have_cxxt_func__0getauxval)' = yes; then \
			echo '#define innocent_pear_HAVE_FUNC_GETAUXVAL 1'; \
		else \
			echo '#undef innocent_pear_HAVE_FUNC_GETAUXVAL'; \
		fi; \
		$(foreach c,PT_TRACE_ME PT_READ_I PT_READ_D PT_READ_U, \
			if test '$(conf_Have_cxxt_const_$(subst \
			    _,_1,$(subst __,,$c)))' = yes; then \
				echo \
				 '#define innocent_pear_HAVE_CONST_$c 1';\
			else	echo \
				 '#undef innocent_pear_HAVE_CONST_$c'; \
			fi; ) \
		$(foreach c,TCOOFF TCOON TCXONC TIOCSTOP TIOCSTART \
		    PR_GET_DUMPABLE PR_SET_DUMPABLE FS_IOC_GETFLAGS \
		    FS_IOC_GETVERSION, \
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
		if test '$(conf_Have_ct_opt_fno_integrated_as)' = yes; then \
			echo '#define' \
			  'innocent_pear_CC_FOR_TARGET_DECOUPLE_AS 1'; \
		else	echo '#undef' \
			  'innocent_pear_CC_FOR_TARGET_DECOUPLE_AS'; \
		fi; \
		if test '$(conf_Have_cxxt_opt_fwritable_strings)' = yes; then \
			echo '#define' \
			  'innocent_pear_CXX_FOR_TARGET_HAVE_WRITABLE_STRINGS'\
			  1; \
		else	echo '#undef' \
			  'innocent_pear_CXX_FOR_TARGET_HAVE_WRITABLE_STRINGS'\
			  ; \
		fi; \
		if test '$(conf_Have_cxxt_opt_wrapper)' = yes; then \
			echo '#define' \
			  'innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER 1'; \
		else	echo '#undef' \
			  'innocent_pear_CXX_FOR_TARGET_HAVE_OPT_WRAPPER'; \
		fi; \
		if test '$(conf_Have_ct_opt_wrapper)' = yes; then \
			echo '#define' \
			  'innocent_pear_CC_FOR_TARGET_HAVE_OPT_WRAPPER 1'; \
		else	echo '#undef' \
			  'innocent_pear_CC_FOR_TARGET_HAVE_OPT_WRAPPER'; \
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

# for debugging
test/test-%.debug.passed: test/test-%.debug test/test-%.good
ifeq "yes" "$(conf_Have_appb_sed)"
ifeq "yes" "$(conf_Have_appb_base64)"
ifeq "yes" "$(conf_Have_appb_head)"
ifeq "yes" "$(conf_Have_appb_xz)"
	@case "$*" in \
	    doge*) \
		echo "* base64 dump of xz'd head of $< :"; \
		xz -9c <'$<' | base64 | head -n 256 | sed 's,^,*  ,';; \
	esac >&2
endif
endif
endif
ifeq "yes" "$(conf_Have_appb_readelf)"
	@case "$*" in \
	    doge*) \
		echo "* readelf -e -W of $< :"; \
		readelf -e -W '$<' | sed 's,^,*  ,'; \
		echo "* readelf -s -W head of $< :"; \
		readelf -s -W '$<' | head -n 100 | sed 's,^,*  ,';; \
	esac >&2
endif
endif
	@echo "* running test $<" >&2
	@LANG=en_US.UTF-8 $(conf_Target_exec) ./$< >$(@:.passed=.1.tmp) || \
	    (res=$$? && \
	     echo "* base64 dump of xz'd $< :" >&2 && \
	     xz -9c <'$<' | base64 | sed 's,^,*  ,' && \
	     echo "* $< exited with error: $$res" >&2 && \
	     $(RM) $(@:.passed=.1.tmp) $(@:.passed=.2.tmp) && \
	     exit 1)
	@LANG=en_US.UTF-8 diff -U2 $(word 2,$+) $(@:.passed=.1.tmp) || \
	    (echo "* base64 dump of xz'd $< :" >&2 && \
	     xz -9c <'$<' | base64 | sed 's,^,*  ,' && \
	     echo "* $<'s expected output and actual output differ" >&2 && \
	     $(RM) $(@:.passed=.1.tmp) $(@:.passed=.2.tmp) && \
	     exit 1)
	@echo "* $< passed" >&2
	@$(RM) $(@:.passed=.1.tmp)

test/test-%.passed: test/test-% test/test-%.good
ifeq "yes" "$(conf_Have_appb_sed)"
ifeq "yes" "$(conf_Have_appb_base64)"
ifeq "yes" "$(conf_Have_appb_head)"
ifeq "yes" "$(conf_Have_appb_xz)"
	@case "$*" in \
	    doge*) \
		echo "* base64 dump of xz'd head of $< :"; \
		xz -9c <'$<' | base64 | head -n 256 | sed 's,^,*  ,';; \
	esac >&2
endif
endif
endif
ifeq "yes" "$(conf_Have_appb_readelf)"
	@case "$*" in \
	    doge*) \
		echo "* readelf -e -W of $< :"; \
		readelf -e -W '$<' | sed 's,^,*  ,'; \
		echo "* readelf -s -W head of $< :"; \
		readelf -s -W '$<' | head -n 100 | sed 's,^,*  ,';; \
	esac >&2
endif
endif
	@echo "* running test $<" >&2
	@LANG=en_US.UTF-8 $(conf_Target_exec) ./$< >$(@:.passed=.1.tmp) \
	    2>$(@:.passed=.2.tmp) ||\
	    (res=$$? && \
	     echo "* base64 dump of xz'd $< :" >&2 && \
	     xz -9c <'$<' | base64 | sed 's,^,*  ,' && \
	     echo "* $< exited with error: $$res" >&2 && \
	     $(RM) $(@:.passed=.1.tmp) $(@:.passed=.2.tmp) && \
	     exit 1)
	@LANG=en_US.UTF-8 diff -U2 /dev/null $(@:.passed=.2.tmp) || \
	    (echo "* base64 dump of xz'd $< :" >&2 && \
	     xz -9c <'$<' | base64 | sed 's,^,*  ,' && \
	     echo "* $< produced output on stderr" >&2 && \
	     $(RM) $(@:.passed=.1.tmp) $(@:.passed=.2.tmp) && \
	     exit 1)
	@LANG=en_US.UTF-8 diff -U2 $(word 2,$+) $(@:.passed=.1.tmp) || \
	    (echo "* base64 dump of $< :" >&2 && \
	     xz -9c <'$<' | base64 | sed 's,^,*  ,' && \
	     echo "* $<'s expected output and actual output differ" >&2 && \
	     $(RM) $(@:.passed=.1.tmp) $(@:.passed=.2.tmp) && \
	     exit 1)
	@echo "* $< passed" >&2
	@$(RM) $(@:.passed=.1.tmp) $(@:.passed=.2.tmp)

# for debugging
test/test-%.debug: test/test-%.debug.o
	time $(conf_Host_exec) $(wrap_cxx.staged) -Xinnocent-pear -debug-doge \
	    $(CXXFLAGS_FOR_TARGET.test) $(LDFLAGS_FOR_TARGET) -o$@ \
	    $^ $(LDLIBS_FOR_TARGET)

test/test-%: test/test-%.o
	time $(conf_Host_exec) $(wrap_cxx.staged) $(CXXFLAGS_FOR_TARGET.test) \
	    $(LDFLAGS_FOR_TARGET) -o$@ $^ $(LDLIBS_FOR_TARGET)

test/test-%.o: test/test-%.cc

test/test-%.o: test/test-%.c

# for debugging
test/test-%.debug.o: test/test-%.cc

test/test-orly-wut \
test/test-orly-wut.o \
test/test-orly-wut.s : state = 0x293c42fc93032e55

test/test-orly-wut.o \
test/test-orly-wut.s : \
    CXXFLAGS_FOR_TARGET.test = $(CXXFLAGS_FOR_TARGET) -DSTATE=$(state)

test/test-orly-wut: test/test-orly-wut.o test/test-orly-wut.ld \
    bin/innocent-pear-doge
	time $(conf_Host_exec) $(wrap_cxx.staged) $(CXXFLAGS_FOR_TARGET) \
	    $(LDFLAGS_FOR_TARGET) -o$@.tmp $(filter %.o %.ld,$^) \
	    $(LDLIBS_FOR_TARGET)
	bin/innocent-pear-doge $@.tmp $@ __doge_start __doge_end $(state) -v
	$(RM) $@.tmp

test/test-doge.debug \
test/test-doge.debug.o \
test/test-doge.debug.s : \
    CXXFLAGS_FOR_TARGET.test = $(CXXFLAGS_FOR_TARGET) -Xinnocent-pear -doge -v

test/test-doge-abs-reloc.debug \
test/test-doge-abs-reloc.debug.o \
test/test-doge-abs-reloc.debug.s \
test/test-doge-eh.debug \
test/test-doge-eh.debug.o \
test/test-doge-eh.debug.s : \
    CXXFLAGS_FOR_TARGET.test = $(CXXFLAGS_FOR_TARGET) -Xinnocent-pear -doge

test/test-doge \
test/test-doge.o \
test/test-doge.s \
test/test-doge-with-c \
test/test-doge-with-c.o \
test/test-doge-with-c.s \
test/test-doge-with-dawg \
test/test-doge-with-dawg.o \
test/test-doge-with-dawg.s \
test/test-doge-abs-reloc \
test/test-doge-abs-reloc.o \
test/test-doge-abs-reloc.s \
test/test-doge-eh \
test/test-doge-eh.o \
test/test-doge-eh.s : \
    CXXFLAGS_FOR_TARGET.test = $(CXXFLAGS_FOR_TARGET) -Xinnocent-pear -doge -s

test/test-doge-with-c \
test/test-doge-with-c.o \
test/test-doge-with-c.s : \
    CFLAGS_FOR_TARGET.test = $(CFLAGS_FOR_TARGET) -Xinnocent-pear -doge -s

test/test-doge-eh: test/test-doge-eh.o test/test-doge-eh.sub.o

test/test-doge-eh.debug: test/test-doge-eh.debug.o \
    test/test-doge-eh.sub.debug.o

define preproc_for_host
	mkdir -p $(@D)
	time $(CXX) -E -x c++ $(CPPFLAGS) $(CXXFLAGS) -o$@.tmp $<
	time $(conf_Host_exec) share/innocent-pear/omnomnom <$@.tmp >$@.2.tmp
	mv $@.2.tmp $@
	$(RM) $@.tmp
endef

define keccak_cp
	mkdir -p $(@D)
	cp $^ $@.tmp
	mv $@.tmp $@
endef

bin/innocent-pear-c++: bin/innocent-pear-c++.o share/innocent-pear/epic.o \
    share/innocent-pear/keyboard.o share/innocent-pear/moar.o \
    share/innocent-pear/sleepier.o infra/keccak/KeccakPRG.o \
    infra/keccak/KeccakDuplex.o infra/keccak/KeccakP-1600-reference.o

bin/innocent-pear-cc: bin/innocent-pear-cc.o share/innocent-pear/epic.o \
    share/innocent-pear/keyboard.o share/innocent-pear/moar.o \
    share/innocent-pear/sleepier.o infra/keccak/KeccakPRG.o \
    infra/keccak/KeccakDuplex.o infra/keccak/KeccakP-1600-reference.o

bin/innocent-pear-doge: bin/innocent-pear-doge.o \
    share/innocent-pear/epic.o share/innocent-pear/lolrus.o \
    share/innocent-pear/sleepier.o

bin/innocent-pear-dogecoin: bin/innocent-pear-dogecoin.o \
    share/innocent-pear/epic.o share/innocent-pear/lolrus.o \
    share/innocent-pear/sleepier.o

share/innocent-pear/calm: share/innocent-pear/calm.o \
    share/innocent-pear/epic.o share/innocent-pear/keyboard.o \
    share/innocent-pear/sleepier.o

$(foreach m,$(modules.host), \
    $(eval $m: $(m:.o=.ii)))

# Assume we are using libstdc++ if ::__gnu_cxx::__verbose_terminate_handler()
# is present.  Otherwise, assume nothing.
#
bin/%.ii share/innocent-pear/%.ii infra/keccak/%.ii: \
    CPPFLAGS += -Dinnocent_pear_HOST_PREFIX=\"$(conf_Prefix)\" \
		-Dinnocent_pear_TARGET_PREFIX=\"$(conf_Target_prefix)\" \
		-Dinnocent_pear_CC_FOR_TARGET=\"$(CC_FOR_TARGET)\" \
		-Dinnocent_pear_CXX_FOR_TARGET=\"$(CXX_FOR_TARGET)\" \
		-Dinnocent_pear_STRIP_FOR_TARGET=\"$(STRIP_FOR_TARGET)\" \
		$(if $(filter yes,$(conf_Have_bfd_strip_opt_strip_all)), \
		    -Dinnocent_pear_STRIP_FOR_TARGET_HAVE_OPT_STRIP_ALL, \
		    -Uinnocent_pear_STRIP_FOR_TARGET_HAVE_OPT_STRIP_ALL) \
		$(if $(filter yes,$(conf_Dyn_ld_cxxt)), \
		    -Dinnocent_pear_DYN_LD_CXX_TARGET, \
		    -Uinnocent_pear_DYN_LD_CXX_TARGET) \
		$(if $(filter yes,$(conf_Dyn_ld_ct)), \
		    -Dinnocent_pear_DYN_LD_CC_TARGET, \
		    -Uinnocent_pear_DYN_LD_CC_TARGET) \
		$(if $(filter yes,$(conf_Have_cxxt_lib_atomic)), \
		    -Dinnocent_pear_CXX_FOR_TARGET_HAVE_LIB_ATOMIC, \
		    -Uinnocent_pear_CXX_FOR_TARGET_HAVE_LIB_ATOMIC) \
		$(if $(filter yes,$(conf_Have_ct_lib_atomic)), \
		    -Dinnocent_pear_CC_FOR_TARGET_HAVE_LIB_ATOMIC, \
		    -Uinnocent_pear_CC_FOR_TARGET_HAVE_LIB_ATOMIC) \
		$(if $(filter yes,$(conf_Have_cxxt_func_$(or \
			)_0_2gnu_1cxx_0_2verbose_1terminate_1handler)), \
		    -Dinnocent_pear_LIBSTDCXX_CXX_TARGET, \
		    -Uinnocent_pear_LIBSTDCXX_CXX_TARGET)

bin/%: bin/%.o
	time $(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^ $(LDLIBS)

# for debugging
ifeq "$(conf_Have_cxx_opt_fno_integrated_as)" "yes"
bin/%.s : CXXFLAGS += -fno-integrated-as
endif
bin/%.s: bin/%.ii
	time $(CXX) $(CXXFLAGS) -S -o$@ $<

bin/%.o: bin/%.ii
	time $(CXX) $(CXXFLAGS) -c -o$@ $<

bin/%.ii: bin/%.cc $(headers.host) $(headers.target) \
    share/innocent-pear/calm share/innocent-pear/omnomnom
	$(preproc_for_host)

share/innocent-pear/%: share/innocent-pear/%.o
	time $(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^ $(LDLIBS)

share/innocent-pear/%.o: share/innocent-pear/%.ii
	time $(CXX) $(CXXFLAGS) -c -o$@ $<

# for debugging
ifeq "$(conf_Have_cxx_opt_fno_integrated_as)" "yes"
share/innocent-pear/%.s : CXXFLAGS += -fno-integrated-as
endif
share/innocent-pear/%.s: share/innocent-pear/%.ii
	time $(CXX) $(CXXFLAGS) -S -o$@ $<

infra/keccak/%.o: infra/keccak/%.ii $(headers.keccak.host)
	time $(CXX) $(CXXFLAGS) -c -o$@ $<

share/innocent-pear/moar.ii: share/innocent-pear/moar.cc $(headers.host)
	mkdir -p $(@D)
	time $(CXX) -E -x c++ $(CPPFLAGS) $(CXXFLAGS) -o$@ $<

share/innocent-pear/%.ii: share/innocent-pear/%.cc $(headers.host) \
    $(headers.target) share/innocent-pear/omnomnom
	$(preproc_for_host)

infra/keccak/%.ii : CPPFLAGS += -DKeccakP200_excluded \
				-DKeccakP400_excluded \
				-DKeccakP800_excluded

infra/keccak/%.ii: infra/keccak/%.cc $(headers.keccak.host)
	mkdir -p $(@D)
	time $(CXX) -E -x c++ $(CPPFLAGS) $(CXXFLAGS) -o$@ $<

share/innocent-pear/omnomnom: share/innocent-pear/omnomnom.cc \
    share/innocent-pear/moar.o infra/keccak/KeccakPRG.o \
    infra/keccak/KeccakDuplex.o infra/keccak/KeccakP-1600-reference.o \
    $(config.h.host)
	mkdir -p $(@D)
	time $(CXX) $(CPPFLAGS) $(CXXFLAGS) -o$@ $(filter-out %.h,$^)

%.o: %.cc $(headers.target) $(installables.host)
	mkdir -p $(@D)
	time $(conf_Host_exec) $(wrap_cxx.staged) $(CPPFLAGS_FOR_TARGET) \
	    $(CXXFLAGS_FOR_TARGET.test) -c -o$@ $<

%.o: %.c $(headers.target) $(installables.host)
	mkdir -p $(@D)
	time $(conf_Host_exec) $(wrap_cc.staged) $(CPPFLAGS_FOR_TARGET) \
	    $(CFLAGS_FOR_TARGET.test) -c -o$@ $<

# for debugging
%.debug.o: %.cc $(headers.target) $(installables.host)
	mkdir -p $(@D)
	time $(conf_Host_exec) $(wrap_cxx.staged) $(CPPFLAGS_FOR_TARGET) \
	    -Dinnocent_pear_DEBUG=1 $(CXXFLAGS_FOR_TARGET.test) -c -o$@ $<

# for debugging
%.s: %.cc $(headers.target) $(installables.host)
	mkdir -p $(@D)
	time $(conf_Host_exec) $(wrap_cxx.staged) $(CPPFLAGS_FOR_TARGET) \
	    $(CXXFLAGS_FOR_TARGET.test) -S -o$@ $<

share/innocent-pear/%: share/innocent-pear/%.cc
	mkdir -p $(@D)
	time $(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o$@ $< $(LDLIBS)

share/innocent-pear/omnomnom.cc: share/innocent-pear/omnomnom.lxx
	mkdir -p $(@D)
	$(LEX) $(LFLAGS) -t -o$@ $< >$@.tmp
	mv $@.tmp $@

infra/keccak/KeccakPRG.h: KeccakCodePackage/Modes/KeccakPRG.h
	$(keccak_cp)

infra/keccak/KeccakPRG.cc: KeccakCodePackage/Modes/KeccakPRG.c
	$(keccak_cp)

infra/keccak/KeccakPRG.inc: KeccakCodePackage/Modes/KeccakPRG.inc
	$(keccak_cp)

infra/keccak/align.h: KeccakCodePackage/Common/align.h
	$(keccak_cp)

infra/keccak/brg_endian.h: KeccakCodePackage/Common/brg_endian.h
	$(keccak_cp)

infra/keccak/KeccakDuplex.h: KeccakCodePackage/Constructions/KeccakDuplex.h
	$(keccak_cp)

infra/keccak/KeccakDuplex.cc: KeccakCodePackage/Constructions/KeccakDuplex.c
	$(keccak_cp)

infra/keccak/KeccakDuplex.inc: KeccakCodePackage/Constructions/KeccakDuplex.inc
	$(keccak_cp)

infra/keccak/KeccakP-1600-SnP.h: \
    KeccakCodePackage/SnP/KeccakP-1600/Reference/KeccakP-1600-SnP.h
	$(keccak_cp)

infra/keccak/KeccakP-1600-reference.cc: \
    KeccakCodePackage/SnP/KeccakP-1600/Reference/KeccakP-1600-reference.c
	$(keccak_cp)

.PHONY: test/test-%.passed test/test-%.debug.passed

.PRECIOUS: config.cache %.ii %.cc %.s %.debug %.debug.o %.o bin/%.o \
    share/innocent-pear/%.o helper/% $(tests.target) $(installables.host)
