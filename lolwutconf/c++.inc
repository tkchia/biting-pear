#!/bin/sh

conf_mod c++.common

conf__cxx_chk_compiler_with() {
	local cxxflags ldlibs
	cxxflags="$1"
	ldlibs="$2"
	shift 2
	if conf__cxxc_chk_compiler_with "$CXX" "$CPPFLAGS" "$cxxflags" \
	    "$LDFLAGS" "$ldlibs" "$conf_Host_exec" ${1+"$@"}
	then	return 0
	else	return $?
	fi
}

conf__cxx_compile_prog() {
	local prog
	conf_cxx_chk_compiler_and_executor
	if conf__in_help_mode
		then return 0; fi
	prog="$1"
	shift
	src="$prog.cc"
	(
		for line in ${1+"$@"}
			do echo "$line"; done
	) >"$src"
	$CXX $CPPFLAGS $CXXFLAGS $LDFLAGS -o"$prog" "$src" $LDLIBS \
	    >/dev/null 2>&1 || res=1
	rm -f "$src"
	return $res
}

conf_cxx_chk_compiler_and_executor() {
	local save_ifs arch rest ld_prefix
	if test -n "$conf_Have_cxx_compiler"
		then return 0; fi
	conf__add_var CXX CPPFLAGS CXXFLAGS LDFLAGS LDLIBS \
	    conf_Have_cxx_compiler conf_Host_exec
	if conf__in_help_mode
		then return 0; fi
	conf__blare_test 'deciding C++ compiler for host'
	if test -n "$conf_Cross_tag" -a -z "$CXX"; then
		conf__cxxc_find_cross_compiler "$conf_Cross_tag" CXX CXXFLAGS
	else
		: "${CXX=g++}"
		: "${CXXFLAGS=-O3}"
	fi
	conf__blare_res "$CXX $CPPFLAGS $CXXFLAGS"
	conf__blare_test 'deciding host program executor'
	if test set != "${conf_Host_exec+set}"; then
		conf__cxxc_find_execor "$conf_Cross_tag" "$CXX" "$CPPFLAGS" \
		    "$CXXFLAGS" "$LDFLAGS" "$LDLIBS" conf_Host_exec
	fi
	conf__blare_res "${conf_Host_exec:-(blank)}"
	conf__blare_test 'checking if C++ compiler and executor for host work'
	if conf__cxx_chk_compiler_with "$CXXFLAGS" "$LDLIBS"; then
		conf__blare_res yes
		conf_Have_cxx_compiler=yes
	else
		conf__blare_res no
		conf__barf 'C++ compiler and/or executor does not work!'
	fi
	conf__cxxc_probe_thumb host "$CXX" "$CPPFLAGS" CXXFLAGS "$LDFLAGS" \
	    "$LDLIBS" "$conf_Host_exec"
}

conf_cxx_probe_cxx11() {
	local extra
	conf_cxx_chk_compiler_and_executor
	if test -n "$conf_Have_cxx11_compiler"
		then return 0; fi
	if conf__in_help_mode
		then return 0; fi
	conf__blare_test 'checking command to enable C++11 support for host'
	conf__add_var conf_Have_cxx11_compiler
	for extra in '' '-std=c++11' '-std=c++0x'; do
		if conf__cxx_chk_compiler_with "$CXXFLAGS $extra" "$LDLIBS" \
		    '#if __cplusplus < 201103L' '#error' '#endif'; then
			CXXFLAGS="$CXXFLAGS $extra"
			conf__blare_res "$CXX $CPPFLAGS $CXXFLAGS"
			conf_Have_cxx11_compiler=yes
			return 0
		fi
	done
	conf__blare_res '(failed; continuing)'
	conf_Have_cxx11_compiler=no
}

conf_cxx_probe_typ() {
	local typ var
	conf_cxx_chk_compiler_and_executor
	if conf__in_help_mode
		then return 0; fi
	typ="$1"
	shift
	var="conf_Have_cxx_typ_`echo "$typ" | sed 's/[^a-zA-Z0-9]/_/g'`"
	if eval test -n \"\$$var\"
		then return 0; fi
	conf__add_var "$var"
	conf__blare_test "testing for host-side C++ type $typ"
	if conf__cxx_chk_compiler_with "$CXXFLAGS" "$LDLIBS" ${1+"$@"} \
	    "typedef $typ conf_foo_t;"
	then	eval $var=yes
	else	eval $var=no
	fi
	eval conf__blare_res \"\$$var\"
}

conf_cxx_probe_lib() {
	local family libs lib
	conf_cxx_chk_compiler_and_executor
	if conf__in_help_mode
		then return 0; fi
	family="$1"
	libs="$2"
	shift 2
	var="conf_Have_cxx_lib_`echo "$family" | \
	    sed 's/[^a-zA-Z0-9]/_/g'`"
	if eval test -n \"\$$var\"
		then return 0; fi
	conf__add_var "$var"
	eval $var=no
	for lib in $libs; do
		conf__blare_test "testing for host-side library $lib"
		if conf__cxx_chk_compiler_with "$CXXFLAGS" "-l$lib $LDLIBS" \
		    ${1+"$@"}; then
			LDLIBS="-l$lib $LDLIBS"
			conf__blare_res yes
			eval $var=yes
			break
		else
			conf__blare_res no
		fi
	done
}

conf_cxx_chk_typ() {
	if conf_cxx_probe_typ ${1+"$@"}
	then	:
	else	conf__barf "type $1 not found!"
	fi
}

conf_cxx_probe_endianness() {
	local prog
	conf_cxx_chk_compiler_and_executor
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Endianness_cxx"
		then return 0; fi
	conf__add_var conf_Endianness_cxx
	conf__blare_test "testing host-side byte order"
	prog="`conf__mktemp lolwutconf`"
	if conf__cxx_compile_prog "$prog" \
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
		conf_Endianness_cxx="`$conf_Host_exec ./"$prog"`"
		case "$conf_Endianness_cxx" in
		    *-endian)	;;
		    *)		conf_Endianness_cxx=unknown;;
		esac
	else
		conf_Endianness_cxx=unknown
	fi
	rm -f "$prog"
	conf__blare_res "$conf_Endianness_cxx"
}

conf_cxx_probe_var_tpls() {
	conf_cxx_probe_cxx11
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Have_cxx_var_tpls"
		then return 0; fi
	conf__add_var conf_Have_cxx_var_tpls
	conf__blare_test \
	    'checking if host-side C++ compiler does variadic templates'
	if conf__cxx_chk_compiler_with "$CXXFLAGS" "$LDLIBS" ${1+"$@"} \
	    'template<class... T> class foo_t { };' \
	    'template<int... V> class bar_t { };' \
	    'extern foo_t<int, char, void *> foo;' \
	    'extern bar_t<1, -1, 6> bar;'
	then	conf_Have_cxx_var_tpls=yes
	else	conf_Have_cxx_var_tpls=no
	fi
	conf__blare_res "$conf_Have_cxx_var_tpls"
}

conf_cxx_probe_decltype() {
	conf_cxx_probe_cxx11
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Have_cxx_decltype"
		then return 0; fi
	conf__add_var conf_Have_cxx_decltype
	conf__blare_test \
	    "checking if host-side C++ compiler understands decltype"
	if conf__cxx_chk_compiler_with "$CXXFLAGS" "$LDLIBS" ${1+"$@"} \
	    'extern int foo;' \
	    'extern decltype(foo << 1) bar;'
	then	conf_Have_cxx_decltype=yes
	else	conf_Have_cxx_decltype=no
	fi
	conf__blare_res "$conf_Have_cxx_decltype"
}

conf_cxx_probe_wchar_typ() {
	conf_cxx_probe_cxx11
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Typ_wchar_cxx"
		then return 0; fi
	conf__add_var conf_Typ_wchar_cxx
	conf__blare_test 'checking host-side type equivalent to wchar_t'
	prog="`conf__mktemp lolwutconf`"
	if conf__cxx_compile_prog "$prog" \
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
		conf_Typ_wchar_cxx="`$conf_Host_exec ./"$prog"`"
		case "$conf_Typ_wchar_cxx" in
		    char16_t | char32_t)	;;
		    *)				conf_Typ_wchar_cxx=unknown;;
		esac
	else
		conf_Typ_wchar_cxx=unknown
	fi
	rm -f "$prog"
	conf__blare_res "$conf_Typ_wchar_cxx"
}
