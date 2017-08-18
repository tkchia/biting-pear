#!/bin/sh

set -e -v
mkdir build-$$
prefix="`pwd`/install-$$"
cd build-$$
sh=sh
while test $# != 0; do
	case "$1" in
	    -x)	sh="$sh -x"
		shift;;
	    -l)	prefix="$HOME/.local"
		shift;;
	    *)	break;;
	esac
done
$sh ../configure --help
mkdir -p "$prefix"
$sh ../configure ${TARGET:+"--target=$TARGET"} --prefix="$prefix" ${1+"$@"}
make
make check
exec make install
