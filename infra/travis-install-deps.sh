#!/bin/sh

set -e -v -- flex binutils-multiarch-dev xz-utils
case "$TARGET" in
    i[3456]86-* | pentium[^4]* | k6-* | athlon-[^f]* | winchip* | \
    c3-* | geode-*)
	set -- ${1+"$@"} g++-multilib gcc-multilib;;
    ia16-elf | ia16-elf,*)
		#
		# I have created a PPA for ia16-elf-gcc, and it now also has
		# packages for Xenial.  Combine this with Andrew Bird et
		# al.'s PPA for dosemu2, fdpp, and Allen Cheung et al.'s
		# comcom32, and we should be good to go.
		#
	sudo add-apt-repository -y ppa:tkchia/build-ia16
	set -- ${1+"$@"} gcc-ia16-elf dos2unix
	if test ! -e dosemu-on-travis-ci/Makefile
		then xz -dc infra/dosemu-on-travis-ci.tar.xz | tar xvf -; fi
	${MAKE-make} -C dosemu-on-travis-ci install;;
    arm-*hf | arm-*hf,*)
	set -- ${1+"$@"} g++-arm-linux-gnueabihf gcc-arm-linux-gnueabihf \
	    qemu-user;;
    arm-*)
	set -- ${1+"$@"} g++-arm-linux-gnueabi gcc-arm-linux-gnueabi \
	    qemu-user;;
esac
if test clang++ = "$CXX_FOR_TARGET" -o clang = "$CC_FOR_TARGET"
	then set -- ${1+"$@"} clang; fi
sudo apt-get update -y
exec sudo apt-get install -y ${1+"$@"}
