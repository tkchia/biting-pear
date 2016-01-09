#!/bin/sh

set -e

# unset any existing variables whose names begin with `conf_'
eval "`set | sed -n '/^conf_/ { s,[^[:alnum:]_].*,,g; s,^,unset ,; p; }'`"

conf__nl='
'

conf__blare() {
	echo "* $*" >&2
}

conf__blare_test() {
	echo -n "* $* ... " >&2
}

conf__blare_res() {
	echo "$*" >&2
}

conf__barf() {
	conf__blare "ERROR: $*"
	exit 1
}

conf__app_exists() {
	type "$1" >/dev/null 2>&1 || which "$1" >/dev/null 2>&1
}

conf__check_general_sanity() {
	local app
	for app in : basename cp dirname echo grep ln mv rm strings seq \
	    test type; do
		if conf__app_exists "$app"; then :; else
			conf__barf "command line program \`$app' not found!"
		fi
	done
	if test ab = "`echo -n a; echo b`"; then :; else
		conf__barf "\`echo' does not understand \`-n'!"; fi
	if test _ = "`echo z | sed s/[[:alpha:]]/_/g`"; then :; else
		conf__barf \
		    "\`sed' does not understand POSIX character classes!"; fi
}

conf__mktemp() {
	local nm sfx
	if nm="`mktemp "$1".XXXXXXXXXX 2>/dev/null`"; then
		echo "$nm"
	else
		(
			set -C
			sfx=$$
			until : >"$1.$sfx" 2>/dev/null; do
				sfx="$sfx+"
				if test ${#sfx} -gt 1000; then
					conf__barf "cannot create" \
					    "temporary file" \
					    "with name starting $1...!"
				fi
			done
			echo "$1.$sfx"
		)
	fi
}

conf__check_sane() {
	case "$1" in
	    *"$conf__nl"*)
		conf__barf "no newlines allowed in $2";;
	esac
}

conf__say() {
	local val
	if eval test xy = x"\${$1+y}"; then
		eval "val=\"\$$1\""
		echo "$1=$val" | \
		    sed 's,[^-_+/=.$[:alnum:][:space:]],\\&,g; s,\$,$$,g'
	fi
}

conf__say_single() {
	conf__say "$1=$2" | sed 's,[[:space:]],\\ ,g'
}

conf__blare_list() {
	local buf buf2 thang
	buf="   "
	for thang in $1; do
		buf2="$buf $thang"
		if test ${#buf2} -ge 63; then
			conf__blare "$buf"
			buf="    $thang"
		else
			buf="$buf2"
		fi
	done
	conf__blare "$buf"
}

conf__in_help_mode() {
	test help = "$conf_Mode"
}

conf__add_var() {
	local var
	for var in ${1+"$@"}; do
		case "$conf_Use_vars" in
		    *" $var "*)
			;;
		    *)	case "$var" in
			    conf_*)
				if conf__in_help_mode
				then :
				else conf_Use_vars="$conf_Use_vars$var "; fi;;
			    *)	conf_Use_vars="$conf_Use_vars$var ";;
			esac
			eval conf__check_sane \"\$$var\" \'\$$var\';;
		esac
	done
}

conf__help() {
	local me
	me="`basename $0`"
	conf__blare "usage:"
	conf__blare "    $me [--srcdir=(dir)] [--prefix=(dir)] \\"
    if test yes = "$conf_Is_canadian_cross"; then
	conf__blare "        [--host=(platform)] [--host-exec=[(runner)]] \\"
	conf__blare "        [--target-prefix=(dir)] \\"
	conf__blare "        [--target=(platform)] [--target-exec=[(runner)]]"
    else
	conf__blare "        [--host=(platform)] [--host-exec=[(runner)]]"
    fi
	conf__blare
	conf__blare "environment variables used:"
	conf__blare_list "$conf_Use_vars"
	conf__blare
	conf__blare "cross compilation notes:"
    if test yes = "$conf_Is_canadian_cross"; then
	conf__blare "  * This project allows a \`Canadian cross' setup.  It"
	conf__blare "    uses a \`build' platform to build development tools "
	conf__blare "    for a \`host' platform, which can then create or"
	conf__blare "    deal with programs for a \`target' platform.  Host ="
	conf__blare "    build on default, and target = host on default."
	conf__blare
    fi
	conf__blare "  * If you specify --host=(platform), \`$me' will look"
	conf__blare "    for cross compilers named (platform)-g++, etc. if"
    if test yes = "$conf_Is_canadian_cross"; then
	conf__blare "    CXX is undefined.  Ditto for --target=(platform)."
	conf__blare "    Also:"
    else
	conf__blare "    CXX is undefined.  Also:"
    fi
	conf__blare
	conf__blare "    - If (platform) is i386-*, i486-*, i586-*, or"
	conf__blare "      i686-*, e.g. i386-linux-gnu, \`$me' will also try"
	conf__blare "      looking for a corresponding 64-bit compiler named"
	conf__blare "      x86_64-*-g++, and pass it -m32, -march= flags."
	conf__blare
	conf__blare "    - If (platform) is armv4*, armv5*, armv6*, armv7*,"
	conf__blare "      or armv8*, \`$me' will also look for arm-*-g++,"
	conf__blare "      and try to use Thumb mode."
	conf__blare
	conf__blare "  * Alternatively, do not specify --host=, but provide"
	conf__blare "    compiler settings in CXX, CXXFLAGS, etc."
	conf__blare
    if test yes = "$conf_Is_canadian_cross"; then
	conf__blare "  * Instead of --target=, too, you can define"
	conf__blare "    CXX_FOR_TARGET, CXXFLAGS_FOR_TARGET, etc."
	conf__blare
    fi
	conf__blare "  * In addition, --host-exec=(runner) specifies a"
	conf__blare "    command for running programs built for the host"
	conf__blare "    system.  If --host= appears but not --host-exec,"
	conf__blare "    \`$me' will try to look for a corresponding Qemu"
	conf__blare "    user-mode emulator, e.g. qemu-arm."
	conf__blare
    if test yes = "$conf_Is_canadian_cross"; then
	conf__blare "  * --target-exec=(runner) specifies a command for"
	conf__blare "    running programs built for the target system."
	conf__blare
	conf__blare "  * The host installation directory (--prefix=) defaults"
	conf__blare "    to /usr/local.  \`$me' tries to derive something"
	conf__blare "    reasonable for the target installation directory"
	conf__blare "    unless --target-prefix= is given."
    else
	conf__blare "  * The host installation directory (--prefix=) defaults"
	conf__blare "    to /usr/local."
    fi
}

conf__find_good_runtime_prefix() {
	local cxx cxxflags good_prefix prefix
	cxx="$1"
	cxxflags="$2"
	good_prefix=
	for arg in -print-file-name=libc.so \
		   -print-file-name=libc.a \
		   -print-libgcc-file-name \
		   -print-file-name=crt1.o
	do
		# we cannot really rely on `realpath' or `readlink' being
		# available, so do this nasty thang...
		prefix="`$cxx $cxxflags $arg`"
		prefix="`echo "$prefix" | xargs dirname`"
		prefix="`cd "$prefix" && pwd`"
		case "$prefix" in
		    */lib)
			prefix="`echo "$prefix" | xargs dirname`"
			if test -z "$good_prefix" -o \
			    ${#prefix} -lt ${#good_prefix}
				then good_prefix="$prefix"; fi;;
		esac
		ld_prefix="`cd "$ld_prefix" && cd .. && pwd`"
	done
	echo "$good_prefix"
}

conf__tweak_host_prefix() {
	conf__blare_test 'tweaking host installation directory'
	case "$conf_Prefix" in
	    /*)	;;
	    *)	conf_Prefix="`pwd`/$conf_Prefix";;
	esac
	conf__blare_res "$conf_Prefix"
	case "$conf_Prefix" in
	    *[,\;:]*)
		conf__blare 'WARNING: directory path contains characters from'
		conf__blare 'WARNING: the set [,;:]; this may cause problems'
		conf__blare 'WARNING: later on';;
	esac
}

conf__tweak_target_prefix() {
	if test -n "$conf_Target_prefix"; then
		conf__blare_test 'tweaking target installation directory'
		case "$conf_Target_prefix" in
		    /*)	;;
		    *)	conf_Target_prefix="`pwd`/$conf_Target_prefix";;
		esac
	else
		conf__blare_test \
		    'deriving a good target installation directory'
		prefix="`conf__find_good_runtime_prefix \
		    "$conf_Host_exec $CXX_FOR_TARGET" "$CXXFLAGS_FOR_TARGET"`"
		case "$prefix" in
		    /usr/local | /usr | /local)
			conf_Target_prefix="$conf_Prefix";;
		    /usr/local/*)
			conf_Target_prefix="$conf_Prefix"/"`echo "$prefix" | \
			    sed s,^/usr/local/,,`";;
		    /usr/*)
			conf_Target_prefix="$conf_Prefix"/"`echo "$prefix" | \
			    sed s,^/usr/,,`";;
		    /local/*)
			conf_Target_prefix="$conf_Prefix"/"`echo "$prefix" | \
			    sed s,^/local/,,`";;
		    '')	conf_Target_prefix="$conf_Prefix/$conf_Crosst_tag";;
		    *)	conf_Target_prefix="$prefix";;
		esac
	fi
	conf__blare_res "$conf_Target_prefix"
}

conf_begin() {
	local opt var
	conf__check_general_sanity
	conf_Srcdir=.
	conf_Prefix=/usr/local
	conf_Target_prefix=
	conf_Cross_tag=
	conf_Crosst_tag=
	unset conf_Host_exec
	conf_Use_vars=' conf_Srcdir conf_Prefix conf_Target_prefix '
	conf_Use_mods=' configure '
	conf_Mode=conf
	conf_Is_canadian_cross=no
	for opt in ${1+"$@"}; do
		conf__check_sane "$opt" arguments
		case "$opt" in
		    --srcdir=?*)
			conf_Srcdir="`echo "$opt" | sed s,^[^=]*=,,`";;
		    --prefix=?*)
			conf_Prefix="`echo "$opt" | sed s,^[^=]*=,,`";;
		    --host=?*)
			conf_Cross_tag="`echo "$opt" | sed s,^[^=]*=,,`";;
		    --host-exec=*)
			conf_Host_exec="`echo "$opt" | sed s,^[^=]*=,,`";;
		    --target-prefix=?*)
			conf_Target_prefix="`echo "$opt" | sed s,^[^=]*=,,`";;
		    --target=?*)
			conf_Crosst_tag="`echo "$opt" | sed s,^[^=]*=,,`";;
		    --target-exec=*)
			conf_Target_exec="`echo "$opt" | sed s,^[^=]*=,,`";;
		    *)	conf_Mode=help;;
		esac
	done
	if conf__in_help_mode
		then return 0; fi
}

conf_mod() {
	local mod
	for mod in ${1+"$@"}; do
		case "$conf_Use_mods" in
		    *" $mod "*)
			;;
		    *)
			if conf__in_help_mode; then :; else
				conf__blare \
				    "reading $conf_Srcdir/lolwutconf/$mod.inc"
			fi
			conf_Use_mods="$conf_Use_mods$mod "
			. "$conf_Srcdir/lolwutconf/$mod.inc";;
		esac
	done
}

conf_end() {
	local var
	if conf__in_help_mode; then
		conf__help
		exit 1
	fi
	conf__tweak_host_prefix
	if test yes = "$conf_Is_canadian_cross"
		then conf__tweak_target_prefix; fi
	conf__blare 'writing config.cache'
	: "${srcdir=`dirname "$0"`}"
	if test \! . = "$conf_Srcdir" -a \! . -ef "$conf_Srcdir"; then
		conf_Separate_build_dir=yes
	else
		conf_Separate_build_dir=no
	fi
	conf__add_var conf_Separate_build_dir
	if test -z "$conf_Target_prefix"; then
		if test -n "$conf_Crosst_tag"; then
			conf_Target_prefix="$conf_Prefix/$conf_Crosst_tag"
		else	conf_Target_prefix="$conf_Prefix"
		fi
	fi
	tmp="`conf__mktemp config.cache`"
	(
		echo "###### AUTOMATICALLY GENERATED `date` ######"
		for var in $conf_Use_vars
			do conf__say $var; done
	) >"$tmp"
	mv "$tmp" config.cache
	if test yes = "$conf_Separate_build_dir"; then
		conf__blare "linking GNUmakefile to $conf_Srcdir/GNUmakefile"
		rm -f GNUmakefile
		if ln -s "$conf_Srcdir"/GNUmakefile GNUmakefile; then :; else
			conf__blare "...failed, copying instead"
			cp "$conf_Srcdir"/GNUmakefile GNUmakefile
		fi
	fi
}
