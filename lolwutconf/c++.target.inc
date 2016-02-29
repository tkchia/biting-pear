#!/bin/sh

conf_mod c++.common
conf_Is_canadian_cross=yes

conf__cxxt_chk_compiler_with() {
	local cxxflags ldlibs
	cxxflags="$1"
	ldlibs="$2"
	shift 2
	if conf__cxxc_chk_compiler_with "$conf_Host_exec $CXX_FOR_TARGET" \
	    "$CPPFLAGS_FOR_TARGET" "$cxxflags" "$LDFLAGS_FOR_TARGET" \
	    "$ldlibs" "$conf_Target_exec" ${1+"$@"}
	then	return 0
	else	return $?
	fi
}

conf__cxxt_compile_prog() {
	local prog
	conf_cxxt_chk_compiler_and_executor
	if conf__in_help_mode
		then return 0; fi
	prog="$1"
	shift
	src="$prog.cc"
	(
		for line in ${1+"$@"}
			do echo "$line"; done
	) >"$src"
	$conf_Host_exec $CXX_FOR_TARGET $CPPFLAGS_FOR_TARGET \
	    $CXXFLAGS_FOR_TARGET $LDFLAGS_FOR_TARGET -o"$prog" "$src" \
	    $LDLIBS_FOR_TARGET >/dev/null 2>&1 || res=1
	rm -f "$src"
	return $res
}

conf_cxxt_chk_compiler_and_executor() {
	local
	if test -n "$conf_Have_cxxt_compiler"
		then return 0; fi
	conf__add_var CXX_FOR_TARGET CPPFLAGS_FOR_TARGET CXXFLAGS_FOR_TARGET \
	    LDFLAGS_FOR_TARGET LDLIBS_FOR_TARGET \
	    conf_Have_cxxt_compiler conf_Target_exec
	if conf__in_help_mode
		then return 0; fi
	conf_cxx_chk_compiler_and_executor
	try_thumb=no
	conf__blare_test 'deciding C++ compiler for target'
	if test -n "$conf_Crosst_tag" -a -z "$CXX_FOR_TARGET"; then
		conf__cxxc_find_cross_compiler "$conf_Crosst_tag" \
		    CXX_FOR_TARGET CXXFLAGS_FOR_TARGET
	elif test -z "$CXX_FOR_TARGET"; then
		: "${CXX_FOR_TARGET=$CXX}"
		: "${CPPFLAGS_FOR_TARGET=$CPPFLAGS}"
		: "${CXXFLAGS_FOR_TARGET=$CXXFLAGS}"
		: "${LDFLAGS_FOR_TARGET=$LDFLAGS}"
		: "${LDLIBS_FOR_TARGET=$LDLIBS}"
	else
		: "${CXXFLAGS_FOR_TARGET=-O3}"
	fi
	conf__blare_res "[$conf_Host_exec] $CXX_FOR_TARGET ` \
	    `$CPPFLAGS_FOR_TARGET $CXXFLAGS_FOR_TARGET"
	conf__blare_test 'deciding target program executor'
	if test set != "${conf_Target_exec+set}"; then
		conf__cxxc_find_execor "$conf_Crosst_tag" \
		    "$conf_Host_exec $CXX_FOR_TARGET" \
		    "$CPPFLAGS_FOR_TARGET" "$CXXFLAGS_FOR_TARGET" \
		    "$LDFLAGS_FOR_TARGET" "$LDLIBS_FOR_TARGET" \
		    conf_Target_exec
	fi
	conf__blare_res "${conf_Target_exec:-(blank)}"
	conf__blare_test \
	    'checking if C++ compiler and executor for target work'
	if conf__cxxt_chk_compiler_with "$CXXFLAGS_FOR_TARGET" \
	    "$LDLIBS_FOR_TARGET"; then
		conf__blare_res yes
		conf_Have_cxxt_compiler=yes
	else
		conf__blare_res no
		conf__barf 'C++ compiler and/or executor does not work!'
	fi
	conf__cxxc_probe_thumb target "$conf_Host_exec $CXX_FOR_TARGET" \
	    "$CPPFLAGS_FOR_TARGET" CXXFLAGS_FOR_TARGET \
	    "$LDFLAGS_FOR_TARGET" "$LDLIBS_FOR_TARGET" "$conf_Target_exec"
}

conf_cxxt_probe_cxx11() {
	local extra
	conf_cxxt_chk_compiler_and_executor
	if test -n "$conf_Have_cxxt_cxx11_compiler"
		then return 0; fi
	if conf__in_help_mode
		then return 0; fi
	conf__blare_test 'checking command to enable C++11 support for target'
	conf__add_var conf_Have_cxxt_cxx11_compiler
	for extra in '' '-std=c++11' '-std=c++0x'; do
		if conf__cxxt_chk_compiler_with \
		    "$CXXFLAGS_FOR_TARGET $extra" "$LDLIBS_FOR_TARGET" \
		    '#if __cplusplus < 201103L' '#error' '#endif'; then
			CXXFLAGS_FOR_TARGET="$CXXFLAGS_FOR_TARGET $extra"
			conf__blare_res "$CXX_FOR_TARGET ` \
			    `$CPPFLAGS_FOR_TARGET $CXXFLAGS_FOR_TARGET"
			conf_Have_cxxt_cxx11_compiler=yes
			return 0
		fi
	done
	conf__blare_res '(failed; continuing)'
	conf_Have_cxxt_cxx11_compiler=no
}

conf_cxxt_probe_typ() {
	local typ var
	conf_cxxt_chk_compiler_and_executor
	if conf__in_help_mode
		then return 0; fi
	typ="$1"
	shift
	var="conf_Have_cxxt_typ_`echo "$typ" | sed 's/[^a-zA-Z0-9]/_/g'`"
	if eval test -n \"\$$var\"
		then return 0; fi
	conf__add_var "$var"
	conf__blare_test "testing for target-side C++ type $typ"
	if conf__cxxt_chk_compiler_with "$CXXFLAGS_FOR_TARGET" \
	    "$LDLIBS_FOR_TARGET" ${1+"$@"} "typedef $typ conf_foo_t;"
	then	eval $var=yes
	else	eval $var=no
	fi
	eval conf__blare_res \"\$$var\"
}

conf_cxxt_probe_lib() {
	local family libs lib
	conf_cxxt_chk_compiler_and_executor
	if conf__in_help_mode
		then return 0; fi
	family="$1"
	libs="$2"
	shift 2
	var="conf_Have_cxxt_lib_`echo "$family" | \
	    sed 's/[^a-zA-Z0-9]/_/g'`"
	if eval test -n \"\$$var\"
		then return 0; fi
	conf__add_var "$var"
	eval $var=no
	for lib in $libs; do
		conf__blare_test "testing for target-side library $lib"
		if conf__cxxt_chk_compiler_with "$CXXFLAGS_FOR_TARGET" \
		    "-l$lib $LDLIBS_FOR_TARGET" ${1+"$@"}; then
			LDLIBS_FOR_TARGET="-l$lib $LDLIBS_FOR_TARGET"
			conf__blare_res yes
			eval $var=yes
			break
		else
			conf__blare_res no
		fi
	done
}

conf_cxxt_chk_typ() {
	if conf_cxxt_probe_typ ${1+"$@"}
	then	:
	else	conf__barf "type $1 not found!"
	fi
}

conf_cxxt_probe_endianness() {
	local prog
	conf_cxxt_chk_compiler_and_executor
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Endianness_cxxt"
		then return 0; fi
	conf__add_var conf_Endianness_cxxt
	conf__blare_test "testing target-side byte order"
	prog="`conf__mktemp lolwutconf`"
	if conf__cxxt_compile_prog "$prog" \
	    "#include <cstring>" \
	    "#include <iostream>" \
	    "using namespace std;" \
	    "typedef unsigned char UC;" \
	    "typedef unsigned int UI;" \
	    "#define M  ((UI)1 + (UI)(UC)~(UC)0)" \
	    "static union { UC c[4]; UI i; } u;" \
	    "int main() {" \
	    "  memset(&u, 0, sizeof u);" \
	    "  u.i = (UC)'g' * M * M * M + (UC)'r' * M * M + \
		     (UC)'o' * M + (UC)'k';" \
	    "  if (memcmp(&u, \"grok\", 4) == 0)" \
	    "    cout << \"big-endian\" << endl;" \
	    "  else if (memcmp(&u, \"korg\", 4) == 0)" \
	    "    cout << \"little-endian\" << endl;" \
	    "  else if (memcmp(&u, \"rgko\", 4) == 0)" \
	    "    cout << \"pdp-endian\" << endl;" \
	    "  else" \
	    "    return 1;" \
	    "  return 0;" \
	    "}"
	then
		conf_Endianness_cxxt="`$conf_Target_exec ./"$prog"`"
		case "$conf_Endianness_cxxt" in
		    *-endian)	;;
		    *)		conf_Endianness_cxxt=unknown;;
		esac
	else
		conf_Endianness_cxxt=unknown
	fi
	rm -f "$prog"
	conf__blare_res "$conf_Endianness_cxxt"
}

conf_cxxt_probe_var_tpls()
{
	conf_cxxt_probe_cxx11
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Have_cxxt_var_tpls"
		then return 0; fi
	conf__add_var conf_Have_cxxt_var_tpls
	conf__blare_test \
	    'checking if target-side C++ compiler does variadic templates'
	if conf__cxxt_chk_compiler_with "$CXXFLAGS_FOR_TARGET" \
	    "$LDLIBS_FOR_TARGET" ${1+"$@"} \
	    'template<class... T> class foo_t { };' \
	    'template<int... V> class bar_t { };' \
	    'extern foo_t<int, char, void *> foo;' \
	    'extern bar_t<1, -1, 6> bar;'
	then	conf_Have_cxxt_var_tpls=yes
	else	conf_Have_cxxt_var_tpls=no
	fi
	conf__blare_res "$conf_Have_cxxt_var_tpls"
}

conf_cxxt_probe_decltype()
{
	conf_cxxt_probe_cxx11
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Have_cxxt_decltype"
		then return 0; fi
	conf__add_var conf_Have_cxxt_decltype
	conf__blare_test \
	    "checking if target-side C++ compiler understands decltype"
	if conf__cxxt_chk_compiler_with "$CXXFLAGS_FOR_TARGET" \
	    "$LDLIBS_FOR_TARGET" ${1+"$@"} \
	    'extern int foo;' \
	    'extern decltype(foo << 1) bar;'
	then	conf_Have_cxxt_decltype=yes
	else	conf_Have_cxxt_decltype=no
	fi
	conf__blare_res "$conf_Have_cxxt_decltype"
}

conf_cxxt_probe_wchar_typ() {
	conf_cxxt_probe_cxx11
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Typ_wchar_cxxt"
		then return 0; fi
	conf__add_var conf_Typ_wchar_cxxt
	conf__blare_test 'checking target-side type equivalent to wchar_t'
	prog="`conf__mktemp lolwutconf`"
	if conf__cxxt_compile_prog "$prog" \
	    "#include <cstring>" \
	    "#include <iostream>" \
	    "using namespace std;" \
	    "int main() {" \
	    "  static const char16_t c16s[] = u\"\\u263a\\u0001f634\";" \
	    "  static const char32_t c32s[] = U\"\\u263a\\U0001f634\";" \
	    "  static const wchar_t wcs[] = L\"\\u263a\\U0001f634\";" \
	    "  if (sizeof(c16s) == sizeof(wcs) &&" \
	    "   memcmp(c16s, wcs, sizeof(c16s)) == 0)" \
	    "    cout << \"char16_t\" << endl;" \
	    "  else if (sizeof(c32s) == sizeof(wcs) &&" \
	    "   memcmp(c32s, wcs, sizeof(c32s)) == 0)" \
	    "    cout << \"char32_t\" << endl;" \
	    "  else" \
	    "    return 1;" \
	    "  return 0;" \
	    "}"
	then
		conf_Typ_wchar_cxxt="`$conf_Target_exec ./"$prog"`"
		case "$conf_Typ_wchar_cxxt" in
		    char16_t | char32_t)	;;
		    *)				conf_Typ_wchar_cxxt=unknown;;
		esac
	else
		conf_Typ_wchar_cxxt=unknown
	fi
	rm -f "$prog"
	conf__blare_res "$conf_Typ_wchar_cxxt"
}

conf_cxxt_probe_overridable_csu_init() {
	local prog
	conf_cxxt_chk_compiler_and_executor
	if conf__in_help_mode
		then return 0; fi
	conf__add_var conf_Have_overridable_csu_init_cxxt
	conf__blare_test "checking if target's __libc_csu_init overridable"
	prog="`conf__mktemp lolwutconf`"
	#
	# Although we only want to override __libc_csu_init(...), we need to
	# also define __libc_csu_fini().  Both are likely to be defined in
	# the same archive member in libc_nonshared.a, so overriding only
	# __libc_csu_init(...) will cause a problem.
	#
	if conf__cxxt_compile_prog "$prog" \
	    'extern "C" void _exit(int);' \
	    'extern "C" void __libc_csu_init(int, char **, char **)' \
	    '  { _exit(0); }' \
	    'extern "C" void __libc_csu_fini()' \
	    '  { _exit(1); }' \
	    'int main()' \
	    '  { return 2; }' && \
	    $conf_Target_exec ./"$prog"
	then	conf_Have_overridable_csu_init_cxxt=yes
	else	conf_Have_overridable_csu_init_cxxt=no
	fi
	rm -f "$prog"
	conf__blare_res "$conf_Have_overridable_csu_init_cxxt"
}
