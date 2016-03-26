#!/bin/sh

set -e -v -- libboost-dev binutils-multiarch-dev
case "$TARGET" in
    arm*)
	set -- ${1+"$@"} g++-arm-linux-gnueabi;;
esac
exec sudo apt-get install -y ${1+"$@"}
