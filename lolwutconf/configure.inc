#!/bin/sh

set -e

# unset any existing variables whose names begin with `conf_'
eval "`set | sed '/^conf_/ { s,[^0-9a-zA-Z_].*,,g; s,^,unset ,; p; }'`"

conf__nl='
'

conf__blare() {
	echo "$*" >&2
}

conf__blare_test() {
	echo -n "$* ... " >&2
}

conf__blare_res() {
	echo "$*" >&2
}

conf__barf() {
	conf_blare "ERROR: $*"
	exit 1
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
		echo "$1=$val" | sed 's,[^-_+/=.$0-9A-Za-z ],\\&,g; s,\$,$$,g'
	fi
}

conf__say_path() {
	conf__say "$1" | sed 's, ,\\ ,g'
}

conf__say_list() {
	local buf buf2 thang
	buf="   "
	for thang in $1; do
		buf2="$buf $thang"
		if test ${#buf2} -ge 75; then
			echo "$buf"
			buf="    $thang"
		else
			buf="$buf2"
		fi
	done
	echo "$buf"
}

conf__add_var() {
	local var
	for var in ${1+"$@"}; do
		case "$conf__use_vars" in
		    "$var" | "$var "* | *" $var" | *" $var "*)
			;;
		    *)	conf__use_vars="$conf__use_vars $var";;
		esac
	done
}

conf_begin() {
	local opt var
	srcdir=.
	prefix=/usr/local
	conf__use_vars=separate_build_dir
	for opt in ${1+"$@"}; do
		conf__check_sane "$opt" arguments
		case "$opt" in
		    --srcdir=?*)
			srcdir="`echo "$opt" | sed s,^[^=]*=,,`";;
		    --prefix=?*)
			prefix="`echo "$opt" | sed s,^[^=]*=,,`";;
		    *)
			echo "usage: `basename "$0"`" \
			     "[--srcdir=(dir)] [--prefix=(dir)]" >&2
			exit 1;;
		esac
	done
	conf__blare 'checking sanity of environment variables'
	for var in $conf__use_vars; do
		eval conf__check_sane \"\$$var\" \'\$$var\'
	done
}

conf_mod() {
	local mod
	for mod in ${1+"$@"}; do
		conf__blare "reading $srcdir/lolwutconf/$mod.inc"
		. "$srcdir/lolwutconf/$mod.inc"
	done
}

conf_end() {
	local var
	conf__blare 'writing config.cache'
	: "${srcdir=`dirname "$0"`}"
	if test \! . = "$srcdir" -a \! . -ef "$srcdir"; then
		separate_build_dir=yes
	else
		separate_build_dir=no
	fi
	tmp="`conf__mktemp config.cache`"
	(
		echo "###### AUTOMATICALLY GENERATED `date` ######"
		conf__say_path srcdir
		conf__say_path prefix
		for var in $conf__use_vars
			do conf__say $var; done
	) >"$tmp"
	mv "$tmp" config.cache
	if test yes = "$separate_build_dir"; then
		conf__blare "linking GNUmakefile to $srcdir/GNUmakefile"
		rm -f GNUmakefile
		if ln -s "$srcdir"/GNUmakefile GNUmakefile; then :; else
			conf__blare "...failed, copying instead"
			cp "$srcdir"/GNUmakefile GNUmakefile
		fi
	fi
}
