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
	"$CXX" $CPPFLAGS $cxxflags $LDFLAGS -o"$prog" "$src" $LDLIBS \
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
	"$CXX_FOR_BUILD" $CPPFLAGS_FOR_BUILD $cxxflags $LDFLAGS_FOR_BUILD \
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

conf_cxx_chk_compiler() {
	if test -n "$conf_Have_cxx_compiler"
		then return 0; fi
	: "${CXX=g++}"
	: "${CXXFLAGS=-O3 -fPIC -Wall}"
	conf__add_var CXX CPPFLAGS CXXFLAGS LDFLAGS LDLIBS \
	    conf_Have_cxx_compiler
	conf__blare_test 'checking if C++ compiler for host works'
	if conf__cxx_chk_compiler_with "$CXXFLAGS"; then
		conf__blare_res yes
		conf_Have_cxx_compiler=yes
	else
		conf__blare_res no
		conf__barf 'C++ compiler does not work!'
	fi
}

conf_cxx_chk_build_compiler() {
	if test -n "$conf_Have_cxx_compiler_for_build"
		then return 0; fi
	conf_cxx_chk_compiler
	: "${CXX_FOR_BUILD=$CXX}"
	: "${CPPFLAGS_FOR_BUILD=$CPPFLAGS}"
	: "${CXXFLAGS_FOR_BUILD=$CXXFLAGS}"
	: "${LDFLAGS_FOR_BUILD=$LDFLAGS}"
	: "${LDLIBS_FOR_BUILD=$LDLIBS}"
	conf__add_var CXX_FOR_BUILD CPPFLAGS_FOR_BUILD CXXFLAGS_FOR_BUILD \
	    LDFLAGS_FOR_BUILD LDLIBS_FOR_BUILD \
	    conf_Have_cxx_compiler_for_build
	if conf__cxx_not_cross; then
		conf_Have_cxx_compiler_for_build=yes
		return 0
	fi
	conf__blare_test 'checking if C++ compiler for build works'
	if conf__cxx_chk_build_compiler_with "$CXXFLAGS"; then
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
	conf__blare_test 'checking command to enable C++11 support'
	for extra in '' '-std=c++11' '-std=c++0x'; do
		if conf__cxx_chk_compiler_with "$CXXFLAGS $extra" \
		    '#if __cplusplus < 201103L' '#error' '#endif'; then
			CXXFLAGS="$CXXFLAGS $extra"
			conf__blare_res "$CXX $CXXFLAGS"
			conf_Have_cxx11_compiler=yes
			return 0
		fi
	done
	conf__blare_res '(failed; continuing)'
	conf_Have_cxx11_compiler=no
}

conf_cxx_probe_typ() {
	local typ var
	conf_cxx_chk_compiler
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
	typ="$1"
	shift
	var="conf_Have_cxx_for_build_typ_`echo "$typ" | \
	    sed 's/[^a-zA-Z0-9]/_/g'`"
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
	    sed 's/[^a-zA-Z0-9]/_/g'`"
	conf_cxx_probe_build_typ "$@"
	if eval test no = \"\$var\"
		then conf__barf "type $1 not found!"; fi
}
