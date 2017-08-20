#!/bin/sh

set -e -v -- flex binutils-multiarch-dev xz-utils
case "$TARGET" in
    i[3456]86-* | pentium[^4]* | k6-* | athlon-[^f]* | winchip* | \
    c3-* | geode-*)
	if (test g++-5 = "$CXX_FOR_TARGET" && ! g++-5 --version) || \
	   (test gcc-5 = "$CC_FOR_TARGET" && ! gcc-5 --version); then
		#
		# This is a hack to get some testing done with g++ (and gcc)
		# 5 under Travis CI's Ubuntu Trusty VM.  Note that
		# installing g++ 5 on a Trusty box may also touch the
		# libraries used by the g++ 4.x setup.
		#
		# When Travis gets an Ubuntu Xenial VM, this can probably
		# go, but until then...
		#
		sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
		sudo apt-get update -y
		set -- ${1+"$@"} g++-5-multilib gcc-5-multilib
	else
		set -- ${1+"$@"} g++-multilib gcc-multilib
	fi;;
    ia16-elf | ia16-elf,*)
		#
		# To reduce testing time, I precompiled g++ and gcc binaries
		# for Linux host and DOS target (from my development fork),
		# as well as dosemu2 Linux binaries.  Here I retrieve the
		# binaries.
		#
		# The tag number may need to be bumped up in the future.
		#
	curl -L -o infra/build-ia16-redist.tar.xz \
	    https://github.com/tkchia/build-ia16/releases/download/` \
		`20170820-redist/build-ia16-redist.tar.xz
	rm -rf prefix
	xzcat infra/build-ia16-redist.tar.xz | tar xvf -
	set -- ${1+"$@"} dos2unix;;
    arm-*hf | arm-*hf,*)
	set -- ${1+"$@"} g++-arm-linux-gnueabihf gcc-arm-linux-gnueabihf \
	    qemu-user;;
    arm-*)
	set -- ${1+"$@"} g++-arm-linux-gnueabi gcc-arm-linux-gnueabi \
	    qemu-user;;
esac
if test clang++ = "$CXX_FOR_TARGET" -o clang = "$CC_FOR_TARGET"
	then set -- ${1+"$@"} clang; fi
exec sudo apt-get install -y ${1+"$@"}
