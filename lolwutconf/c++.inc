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
	if $CXX $CPPFLAGS $cxxflags $LDFLAGS -o"$prog" "$src" $LDLIBS \
	    >/dev/null 2>&1; then
		$conf_Host_exec ./"$prog" >/dev/null 2>&1
	else
		res=1
	fi
	rm -f "$prog" "$src"
	return $res
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
	local save_ifs arch rest try_thumb ld_prefix
	if test -n "$conf_Have_cxx_compiler"
		then return 0; fi
	conf__add_var CXX CPPFLAGS CXXFLAGS LDFLAGS LDLIBS \
	    conf_Have_cxx_compiler conf_Host_exec
	if conf__in_help_mode
		then return 0; fi
	try_thumb=no
	conf__blare_test 'deciding C++ compiler for host'
	: "${CXXFLAGS=-O3}"
	if test -n "$conf_Cross_tag" -a -z "$CXX"; then
		# handle x86-32 platforms specially
		case "$conf_Cross_tag" in
		    i[3456]86-*)
			if conf__app_exists "${conf_Cross_tag}g++"; then
				CXX="${conf_Cross_tag}g++"
			else
				save_ifs="$IFS"
				IFS=-
				set '--' $conf_Cross_tag
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
				set '--' $conf_Cross_tag
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
	fi
	conf__blare_res "$CXX $CPPFLAGS $CXXFLAGS"
	conf__blare_test 'deciding host program executor'
	if test set != "${conf_Host_exec+set}"; then
		conf_Host_exec=
		if test -z "$conf_Cross_tag"; then
			:	# nothing to do
		elif conf__cxx_chk_compiler_with "$CXXFLAGS"; then
			:	# nothing to do too -- no need for a separate
				# program to run host-side commands
		else
			case "$conf_Cross_tag" in
			    i[3456]86-*)
				conf_Host_exec=qemu-i386;;
			    armv[45678]* | arm-*)
				conf_Host_exec=qemu-arm;;
			    aarch64-* | armeb-* | cris-* | m68k-* | \
			    microblaze-* | microblazeel-* | mips-* | \
			    mips64-* | mips64el-* | mipsel-* | mipsn32-* | \
			    mipsn32el-* | or32-* | ppc-* | ppc64-* | \
			    ppc64abi32-* | s390x-* | sh4-* | sh4eb-* | \
			    sparc-* | sparc32plus-* | sparc64-* | x86_64-*)
				# the above pattern is not really tested...
				save_ifs="$IFS"
				set '--' $conf_Cross_tag
				conf_Host_exec=qemu-"$1"
				IFS="$save_ifs";;
			    *)	# OK, we do not really know what to do here...
				;;
			esac
			if test -n "$conf_Host_exec"; then
				# we cannot really rely on `realpath' or
				# `readlink' being available, so do this
				# nasty thang...
				ld_prefix="`$CXX $CXXFLAGS \
				    -print-file-name=libc.so`"
				ld_prefix="`echo "$ld_prefix" | \
				    xargs dirname`"
				ld_prefix="`cd "$ld_prefix" && cd .. && pwd`"
				conf_Host_exec="$conf_Host_exec -L $ld_prefix"
			fi
		fi
	fi
	conf__blare_res "${conf_Host_exec:-(blank)}"
	conf__blare_test 'checking if C++ compiler and executor for host work'
	if conf__cxx_chk_compiler_with "$CXXFLAGS"; then
		conf__blare_res yes
		conf_Have_cxx_compiler=yes
	else
		conf__blare_res no
		conf__barf 'C++ compiler and/or executor does not work!'
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
		conf__blare_res '(failed; continuing)'
	fi
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
	if conf__cxx_chk_compiler_with "$CXXFLAGS" ${1+"$@"} \
	    "typedef $typ conf_foo_t;"
	then	eval $var=yes
	else	eval $var=no
	fi
	eval conf__blare_res \"\$$var\"
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
		rm -f "$prog"
		case "$conf_Endianness_cxx" in
		    *-endian)	;;
		    *)		conf_Endianness_cxx_=unknown;;
		esac
	else
		conf_Endianness_cxx=unknown
	fi
	conf__blare_res "$conf_Endianness_cxx"
}

conf_cxx_probe_var_tpls()
{
	conf_cxx_probe_cxx11
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Have_cxx_var_tpls"
		then return 0; fi
	conf__add_var conf_Have_cxx_var_tpls
	conf__blare_test 'checking if C++ compiler does variadic templates'
	if conf__cxx_chk_compiler_with "$CXXFLAGS" ${1+"$@"} \
	    'template<class... T> class foo_t { };' \
	    'template<int... V> class bar_t { };' \
	    'extern foo_t<int, char, void *> foo;' \
	    'extern bar_t<1, -1, 6> bar;'
	then	conf_Have_cxx_var_tpls=yes
	else	conf_Have_cxx_var_tpls=no
	fi
	conf__blare_res "$conf_Have_cxx_var_tpls"
}
