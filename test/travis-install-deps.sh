#!/bin/sh

set -e -v -- libboost-dev binutils-multiarch-dev
case "$TARGET" in
    i[3456]86-*)
	set -- ${1+"$@"} g++-multilib;;
    armv[45678]* | arm-*)
	set -- ${1+"$@"} g++-arm-linux-gnueabi qemu-user;;
esac
exec sudo apt-get install -y ${1+"$@"}
