#!/bin/sh

set -e

# unset any existing variables whose names begin with `conf_'
eval "`set | sed '/^conf_/ { s,[^[:alnum:]_].*,,g; s,^,unset ,; p; }'`"

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
	for app in : basename cp dirname echo ln mv rm test type; do
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
	local - nm sfx
	if nm="`mktemp "$1".XXXXXXXXXX 2>/dev/null`"; then
		echo "$nm"
	else
		set -C
		sfx=$$
		until : >"$1.$sfx" 2>/dev/null; do
			sfx="$sfx+"
			if test ${#sfx} -gt 1000; then
				conf__barf "cannot create temporary file" \
				    "with name starting $1...!"
			fi
		done
		echo "$1.$sfx"
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

conf__spirit_var() {
	if eval test -n \"\${$2+set}\"; then
		eval conf__check_sane \"\$$2\" \'\$$2\'
		eval $1=\"\$$2\"
	else
		eval unset $1
	fi
	eval unset $2
}

conf__help() {
	local me
	me="`basename $0`"
	conf__blare "usage:"
	conf__blare "    $me [--srcdir=(dir)] [--prefix=(dir)] \\"
	conf__blare "        [--host=(platform)]"
	conf__blare
	conf__blare "environment variables used:"
	conf__blare_list "$conf_Use_vars"
	conf__blare
	conf__blare "cross compilation notes:"
	conf__blare "  * If you specify --host=(platform), \`$me' will look"
	conf__blare "    for cross compilers named (platform)-g++, etc."
	conf__blare "    CXX, CXXFLAGS, and so on are treated as compiler"
	conf__blare "    options on the _build_ side.  Also:"
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
	conf__blare "    _host_ settings in CXX, CXXFLAGS, etc., and _build_"
	conf__blare "    settings in CXX_FOR_BUILD, CXXFLAGS_FOR_BUILD, etc."
}

conf_begin() {
	local opt var
	conf__check_general_sanity
	conf_Srcdir=.
	conf_Prefix=/usr/local
	conf_Cross_tag=
	conf_Use_vars=' '
	conf_Mode=conf
	for opt in ${1+"$@"}; do
		conf__check_sane "$opt" arguments
		case "$opt" in
		    --srcdir=?*)
			conf_Srcdir="`echo "$opt" | sed s,^[^=]*=,,`";;
		    --prefix=?*)
			conf_Prefix="`echo "$opt" | sed s,^[^=]*=,,`";;
		    --host=?*)
			conf_Cross_tag="`echo "$opt" | sed s,^[^=]*=,,`"-;;
		    *)	conf_Mode=help;;
		esac
	done
	if conf__in_help_mode
		then return 0; fi
	if test -n "$conf_Cross_tag"; then
		conf__spirit_var CXX_FOR_BUILD CXX
		conf__spirit_var CPPFLAGS_FOR_BUILD CPPFLAGS
		conf__spirit_var CXXFLAGS_FOR_BUILD CXXFLAGS
		conf__spirit_var LDFLAGS_FOR_BUILD LDFLAGS
		conf__spirit_var LDLIBS_FOR_BUILD LDLIBS
	fi
}

conf_mod() {
	local mod
	for mod in ${1+"$@"}; do
		if conf__in_help_mode; then :; else
			conf__blare "reading $conf_Srcdir/lolwutconf/$mod.inc"
		fi
		. "$conf_Srcdir/lolwutconf/$mod.inc"
	done
}

conf_end() {
	local var
	if conf__in_help_mode; then
		conf__help
		exit 1
		exit 1
	fi
	conf__blare 'writing config.cache'
	: "${srcdir=`dirname "$0"`}"
	if test \! . = "$conf_Srcdir" -a \! . -ef "$conf_Srcdir"; then
		separate_build_dir=yes
	else
		separate_build_dir=no
	fi
	tmp="`conf__mktemp config.cache`"
	(
		echo "###### AUTOMATICALLY GENERATED `date` ######"
		conf__say_single srcdir "$conf_Srcdir"
		conf__say_single prefix "$conf_Prefix"
		if test \! . = "$conf_Srcdir" -a \! . -ef "$conf_Srcdir"; then
			conf__say_single separate_build_dir yes
		else
			conf__say_single separate_build_dir no
		fi
		for var in $conf_Use_vars
			do conf__say $var; done
	) >"$tmp"
	mv "$tmp" config.cache
	if test yes = "$separate_build_dir"; then
		conf__blare "linking GNUmakefile to $conf_Srcdir/GNUmakefile"
		rm -f GNUmakefile
		if ln -s "$conf_Srcdir"/GNUmakefile GNUmakefile; then :; else
			conf__blare "...failed, copying instead"
			cp "$conf_Srcdir"/GNUmakefile GNUmakefile
		fi
	fi
}
