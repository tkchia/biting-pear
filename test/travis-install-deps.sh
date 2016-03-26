#!/bin/sh

set -e -v -- libboost-dev binutils-multiarch-dev
case "$TARGET" in
    i[3456]86)
	set -- ${1+"$@"} lib32stdc++-4.8-dev;;
    arm*)
	set -- ${1+"$@"} g++-arm-linux-gnueabi qemu-user;;
esac
exec sudo apt-get install -y ${1+"$@"}
