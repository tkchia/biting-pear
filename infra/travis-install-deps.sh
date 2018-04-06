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
		# (March 2018) w00t!  I have created a PPA for ia16-elf-gcc,
		# and it now also has packages for Trusty.
		#
		# Combine this with Andrew Bird et al.'s PPA for dosemu,
		# plus FreeDOS binaries, and we should be good to go.
		#
	sudo add-apt-repository -y ppa:tkchia/build-ia16
	sudo add-apt-repository -y ppa:dosemu2/ppa
	sudo apt-get update -y
	set -- ${1+"$@"} gcc-ia16-elf
	tar xvzf infra/dosemu-freedos-1.0-bin.tgz
		#
		# Well, we do need to tweak the FreeDOS setup a little so
		# that things will work.  Install dosemu2 and dos2unix here,
		# since we need them now.
		#
	sudo apt-get install -y dosemu2 dos2unix
	rm -rf ~/.dosemu
	mkdir -p ~/.dosemu/drives
	ln -s "`pwd`"/dosemu/freedos ~/.dosemu/drives/c
	ln -s /usr/share/dosemu/dosemu2-cmds-0.1 ~/.dosemu/drives/d
	rm -f dosemu/freedos/config.sys
	(
		dos2unix </usr/share/dosemu/dosemu2-cmds-0.1/autoexec.bat | \
		    sed 's,e:\\dosemu,c:\\dosemu,g'
		echo
		echo 'dosemu\unix -e'
	) >dosemu/freedos/autoexec.bat
	cat dosemu/freedos/autoexec.bat;;
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
