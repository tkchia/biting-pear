#!/bin/sh

set -e -v
mkdir build-$$
tgt="`echo "$TARGET" | sed 's/,.*$//'`"
if test -d prefix -a -x prefix/bin/"$tgt"-gcc -a \
    -x prefix/bin/"$tgt"-g++; then
	PATH="`pwd`/prefix/bin:$PATH"
	: "${CFLAGS_FOR_TARGET=-Os -Wall -static}"
	CFLAGS_FOR_TARGET="-B`pwd`/prefix/bin/$tgt- $CFLAGS_FOR_TARGET"
	: "${CXXFLAGS_FOR_TARGET=-Os -Wall -static}"
	CXXFLAGS_FOR_TARGET="-B`pwd`/prefix/bin/$tgt- $CXXFLAGS_FOR_TARGET"
	export PATH CFLAGS_FOR_TARGET CXXFLAGS_FOR_TARGET
fi
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
