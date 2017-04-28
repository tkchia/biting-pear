#!/bin/sh

set -e -v
mkdir build-$$
cd build-$$
case "$1" in
    -x)	sh='sh -x';;
    *)	sh=;;
esac
$sh ../configure --help
$sh ../configure ${TARGET:+"--target=$TARGET"}
make
exec make check
