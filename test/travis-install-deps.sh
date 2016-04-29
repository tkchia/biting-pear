#!/bin/sh

set -e -v -- flex libboost-dev binutils-multiarch-dev
case "$TARGET" in
    i[3456]86-*)
	if test g++-5 = "$CXX_FOR_TARGET" && ! g++-5 --version; then
		#
		# This is a hack to get some testing done with g++ 5 under
		# Travis CI's Ubuntu Trusty VM.  Note that installing g++ 5
		# on a Trusty box may also touch the libraries used by the
		# g++ 4.x setup.
		#
		# When Travis gets an Ubuntu Xenial VM, this can probably
		# go, but until then...
		#
		sudo add-apt-repository ppa:ubuntu-toolchain-r/test
		sudo apt-get update
		set -- ${1+"$@"} g++-5-multilib
	else
		set -- ${1+"$@"} g++-multilib
	fi;;
    armv[45678]* | arm-*)
	set -- ${1+"$@"} g++-arm-linux-gnueabi qemu-user;;
esac
exec sudo apt-get install -y ${1+"$@"}
