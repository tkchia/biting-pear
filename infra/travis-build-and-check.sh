#!/bin/sh

set -e -v
mkdir build-$$
tgt="`echo "$TARGET" | sed 's/,.*$//'`"
inst_prefix="`pwd`/install-$$"
cd build-$$
sh=sh
while test $# != 0; do
	case "$1" in
	    -x)	sh="$sh -x"
		shift;;
	    -l)	inst_prefix="$HOME/.local"
		shift;;
	    *)	break;;
	esac
done
$sh ../configure --help
mkdir -p "$inst_prefix"
$sh ../configure ${TARGET:+"--target=$TARGET"} --prefix="$inst_prefix" \
    ${1+"$@"}
make
make check
exec make install
