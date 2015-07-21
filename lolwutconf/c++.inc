#!/bin/sh

conf__cxx_chk_compiler_with() {
	local cxxflags prog src res line
	cxxflags="$1"
	shift
	prog="`conf__mktemp lolwutconf`"
	src="$prog.cc"
	(
		for line in ${1+"$@"}
			do echo "$line"; done
		echo 'int main() { return 0; }'
	) >"$src"
	res=0
	$CXX $CPPFLAGS $cxxflags $LDFLAGS -o"$prog" "$src" $LDLIBS \
	    >/dev/null 2>&1 || res=1
	rm -f "$prog" "$src"
	return $res
}

conf__cxx_chk_build_compiler_with() {
	local cxxflags prog src res line
	cxxflags="$1"
	shift 1
	prog="`conf__mktemp lolwutconf`"
	src="$prog.cc"
	(
		for line in ${1+"$@"}
			do echo "$line"; done
		echo 'int main() { return 0; }'
	) >"$src"
	res=0
	$CXX_FOR_BUILD $CPPFLAGS_FOR_BUILD $cxxflags $LDFLAGS_FOR_BUILD \
	    -o"$prog" "$src" $LDLIBS_FOR_BUILD \
	    >/dev/null 2>&1 || res=1
	rm -f "$prog" "$src"
	return $res
}

conf__cxx_not_cross() {
	test x"${CXX_FOR_BUILD-$CXX}" = x"$CXX" -a \
	     x"${CPPFLAGS_FOR_BUILD-$CPPFLAGS}" = x"$CPPFLAGS" -a \
	     x"${CXXFLAGS_FOR_BUILD-$CXXFLAGS}" = x"$CXXFLAGS" -a \
	     x"${LDFLAGS_FOR_BUILD-$LDFLAGS}" = x"$LDFLAGS" -a \
	     x"${LDLIBS_FOR_BUILD-$LDLIBS}" = x"$LDLIBS"
}

conf__cxx_compile_prog() {
	local prog
	conf_cxx_chk_compiler
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

conf__cxx_compile_build_prog() {
	local prog
	conf_cxx_chk_build_compiler
	if conf__in_help_mode
		then return 0; fi
	prog="$1"
	shift
	src="$prog.cc"
	(
		for line in ${1+"$@"}
			do echo "$line"; done
	) >"$src"
	$CXX_FOR_BUILD $CPPFLAGS_FOR_BUILD $CXXFLAGS_FOR_BUILD \
	    $LDFLAGS_FOR_BUILD -o"$prog" "$src" $LDLIBS_FOR_BUILD \
	    >/dev/null 2>&1 || res=1
	rm -f "$src"
	return $res
}

conf_cxx_chk_compiler() {
	local save_ifs arch rest try_thumb
	if test -n "$conf_Have_cxx_compiler"
		then return 0; fi
	conf__add_var CXX CPPFLAGS CXXFLAGS LDFLAGS LDLIBS \
	    conf_Have_cxx_compiler
	if conf__in_help_mode
		then return 0; fi
	try_thumb=no
	conf__blare_test 'deciding C++ compiler for host'
	if test -n "$conf_Cross_tag"; then
		# handle x86-32 platforms specially
		CXXFLAGS="$CXXFLAGS_FOR_BUILD"
		case "$conf_Cross_tag" in
		    i[3456]86-*)
			if conf__app_exists "${conf_Cross_tag}g++"; then
				CXX="${conf_Cross_tag}g++"
			else
				save_ifs="$IFS"
				IFS=-
				set $conf_Cross_tag
				arch="$1"
				shift
				rest="$*"
				IFS="$save_ifs"
				CXX="x86_64-$rest-g++"
				CXXFLAGS="-m32 -march=$arch $CXXFLAGS"
			fi;;
		    armv[45678]*)
			if conf__app_exists "${conf_Cross_tag}g++"; then
				CXX="${conf_Cross_tag}g++"
			else
				save_ifs="$IFS"
				IFS=-
				set $conf_Cross_tag
				case "$2" in
				    m | a | r)
					arch="$1-$2"
					shift 2;;
				    *)
					arch="$1"
					shift;;
				esac
				rest="$*"
				IFS="$save_ifs"
				CXX="arm-$rest-g++"
				CXXFLAGS="-march=$arch $CXXFLAGS"
				try_thumb=yes
			fi;;
		    *)	CXX="${conf_Cross_tag}g++";;
		esac
	else
		: "${CXX=g++}"
		: "${CXXFLAGS=-O3}"
	fi
	conf__blare_res "$CXX $CPPFLAGS $CXXFLAGS"
	: "${CXXFLAGS=-O3}"
	conf__blare_test 'checking if C++ compiler for host works'
	if conf__cxx_chk_compiler_with "$CXXFLAGS"; then
		conf__blare_res yes
		conf_Have_cxx_compiler=yes
	else
		conf__blare_res no
		conf__barf 'C++ compiler does not work!'
	fi
	if test yes = "$try_thumb"; then
		conf__blare_test \
		    'checking command to enable Thumb mode for host'
		# g++ normally only gives a warning if Thumb mode is not
		# available.  Turn the warning into an error.
		if conf__cxx_chk_compiler_with "$CXXFLAGS -mthumb -Werror";
		then	CXXFLAGS="$CXXFLAGS -mthumb"
			conf__blare_res "$CXX $CPPFLAGS $CXXFLAGS"
			return 0
		fi
	fi
	conf__blare_res '(failed; continuing)'
}

conf_cxx_chk_build_compiler() {
	if test -n "$conf_Have_cxx_compiler_for_build"
		then return 0; fi
	conf__add_var CXX_FOR_BUILD CPPFLAGS_FOR_BUILD CXXFLAGS_FOR_BUILD \
	    LDFLAGS_FOR_BUILD LDLIBS_FOR_BUILD \
	    conf_Have_cxx_compiler_for_build
	if conf__in_help_mode
		then return 0; fi
	conf_cxx_chk_compiler
	conf__blare_test 'deciding C++ compiler for build'
	if test -n "$conf_Cross_tag"; then
		: "${CXX_FOR_BUILD=g++}"
		: "${CXXFLAGS_FOR_BUILD=-O3}"
	else
		: "${CXX_FOR_BUILD=$CXX}"
		: "${CPPFLAGS_FOR_BUILD=$CPPFLAGS}"
		: "${CXXFLAGS_FOR_BUILD=$CXXFLAGS}"
		: "${LDFLAGS_FOR_BUILD=$LDFLAGS}"
		: "${LDLIBS_FOR_BUILD=$LDLIBS}"
	fi
	conf__blare_res \
	    "$CXX_FOR_BUILD $CPPFLAGS_FOR_BUILD $CXXFLAGS_FOR_BUILD"
	if conf__cxx_not_cross; then
		conf_Have_cxx_compiler_for_build=yes
		return 0
	fi
	conf__blare_test 'checking if C++ compiler for build works'
	if conf__cxx_chk_build_compiler_with "$CXXFLAGS_FOR_BUILD"; then
		conf__blare_res yes
		conf_Have_cxx_compiler_for_build=yes
	else
		conf__blare_res no
		conf__barf 'C++ compiler does not work!'
	fi
}

conf_cxx_probe_cxx11() {
	local extra
	conf_cxx_chk_compiler
	if test -n "$conf_Have_cxx11_compiler"
		then return 0; fi
	if conf__in_help_mode
		then return 0; fi
	conf__blare_test 'checking command to enable C++11 support for host'
	conf__add_var conf_Have_cxx11_compiler
	for extra in '' '-std=c++11' '-std=c++0x'; do
		if conf__cxx_chk_compiler_with "$CXXFLAGS $extra" \
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

conf_cxx_probe_build_cxx11() {
	local extra
	conf_cxx_chk_build_compiler
	if test -n "$conf_Have_cxx11_build_compiler"
		then return 0; fi
	if conf__in_help_mode
		then return 0; fi
	conf__add_var conf_Have_cxx11_build_compiler
	if conf__cxx_not_cross; then
		conf_Have_cxx11_build_compiler="$conf_Have_cxx11_compiler"
		return 0
	fi
	conf__blare_test 'checking command to enable C++11 support for build'
	for extra in '' '-std=c++11' '-std=c++0x'; do
		if conf__cxx_chk_build_compiler_with \
		    "$CXXFLAGS_FOR_BUILD $extra" \
		    '#if __cplusplus < 201103L' '#error' '#endif'; then
			CXXFLAGS_FOR_BUILD="$CXXFLAGS_FOR_BUILD $extra"
			conf__blare_res "$CXX $CPPFLAGS $CXXFLAGS"
			conf_Have_cxx11_build_compiler=yes
			return 0
		fi
	done
	conf__blare_res '(failed; continuing)'
	conf_Have_cxx11_build_compiler=no
}

conf_cxx_probe_typ() {
	local typ var
	conf_cxx_chk_compiler
	if conf__in_help_mode
		then return 0; fi
	typ="$1"
	shift
	var="conf_Have_cxx_typ_`echo "$typ" | sed 's/[^a-zA-Z0-9]/_/g'`"
	if eval test -n \"\$$var\"
		then return 0; fi
	conf__add_var "$var"
	conf__blare_test "testing for host-side C++ type $typ"
	if conf__cxx_chk_compiler_with "$CXXFLAGS" ${1+"$@"} \
	    "typedef $typ conf_foo_t;"
	then	eval $var=yes
	else	eval $var=no
	fi
	eval conf__blare_res \"\$$var\"
}

conf_cxx_probe_build_typ() {
	local typ var
	conf_cxx_chk_build_compiler
	if conf__in_help_mode
		then return 0; fi
	typ="$1"
	shift
	var="conf_Have_cxx_for_build_typ_`echo "$typ" | \
	    sed 's/[^[:alnum:]]/_/g'`"
	if eval test -n \"\$$var\"
		then return 0; fi
	conf__add_var "$var"
	conf__blare_test "testing for build-side C++ type $typ"
	if conf__cxx_chk_build_compiler_with "$CXXFLAGS_FOR_BUILD" ${1+"$@"} \
	    "typedef $typ conf_foo_t;"
	then	eval $var=yes
	else	eval $var=no
	fi
	eval conf__blare_res \"\$$var\"
}

conf_cxx_chk_build_typ() {
	local var
	var="conf_Have_cxx_for_build_typ_`echo "$typ" | \
	    sed 's/[^[:alnum:]]/_/g'`"
	conf_cxx_probe_build_typ "$@"
	if eval test no = \"\$var\"
		then conf__barf "type $1 not found!"; fi
}

conf_cxx_probe_build_endianness() {
	conf_cxx_chk_build_compiler
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Endianness_cxx_build"
		then return 0; fi
	conf__add_var conf_Endianness_cxx_build
	conf__blare_test "testing build-side byte order"
	prog="`conf__mktemp lolwutconf`"
	if conf__cxx_compile_build_prog "$prog" \
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
		conf_Endianness_cxx_build="`exec ./"$prog"`"
		rm -f "$prog"
		case "$conf_Endianness_cxx_build" in
		    *-endian)	;;
		    *)		conf_Endianness_cxx_build=unknown;;
		esac
	else
		conf_Endianness_cxx_build=unknown
	fi
	conf__blare_res "$conf_Endianness_cxx_build"
}

conf_cxx_probe_endianness() {
	local prog mm ii pp
	conf_cxx_chk_compiler
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Endianness_cxx"
		then return 0; fi
	conf__add_var conf_Endianness_cxx
	if conf__cxx_not_cross; then
		conf_cxx_probe_build_endianness
		conf_Endianness_cxx="$conf_Endianness_cxx_build"
		return 0
	fi
	conf__blare_test "testing host-side byte order"
	#
	# A somewhat more `portable' version of the grepping test used in
	# autoconf, not relying in specific character sets or character
	# sizes.  -- 20150718
	#
	prog="`conf__mktemp lolwutconf`"
	if conf__cxx_compile_prog "$prog" \
	    "typedef unsigned char UC;" \
	    "typedef unsigned int UI;" \
	    "#define M  ((UI)1 + (UI)(UC)~(UC)0)" \
	    "#define B(w, x, y, z) \
		((UI)(UC)(w) * M * M * M + \
		 (UI)(UC)(x) * M * M + \
		 (UI)(UC)(y) * M + \
		 (UI)(UC)(z))" \
	    "#define L(w, x, y, z)  B(z, y, x, w)" \
	    "#define P(w, x, y, z)  B(x, w, z, y)" \
	    "UI mm[] =" \
	    "  { B('B', 'I', 'G', 'e'), B('n', 'D', 'i', 'a')," \
	    "    B('n', 'S', 'y', 'S'), 0 };" \
	    "UI ii[] =" \
	    "  { L('L', 'i', 'T', 'T'), L('l', 'e', 'E', 'n')," \
	    "    L('D', 'i', 'a', 'n'), 0 };" \
	    "UI pp[] =" \
	    "  { P('p', 'd', 'P', 'e'), P('N', 'd', 'i', 'a')," \
	    "    P('n', 's', 'Y', 's'), 0 };" \
	    "int main(int argc, char **argv)" \
	    "  { return argc < 7 ? mm[argc] + ii[argc] + pp[argc] : 0; }"
	then
		if strings <"$prog" | grep BIGenDianSyS >/dev/null 2>&1
			then mm=yes
			else mm=no; fi
		if strings <"$prog" | grep LiTTleEnDian >/dev/null 2>&1
			then ii=yes
			else ii=no; fi
		if strings <"$prog" | grep pdPeNdiansYs >/dev/null 2>&1
			then pp=yes
			else pp=no; fi
		rm -f "$prog"
		case "$mm,$ii,$pp" in
		    yes,no,no)
			conf_Endianness_cxx=big-endian;;
		    no,yes,no)
			conf_Endianness_cxx=little-endian;;
		    no,no,yes)
			conf_Endianness_cxx=pdp-endian;;
		    *)	conf_Endianness_cxx=unknown;;
		esac
	else
		conf_Endianness_cxx=unknown
	fi
	conf__blare_res "$conf_Endianness_cxx"
}
