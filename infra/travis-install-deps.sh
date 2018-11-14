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
	set -- ${1+"$@"} gcc-ia16-elf
	tar xvzf infra/dosemu-freedos-1.0-bin.tgz
		#
		# Well, we do need to tweak the FreeDOS setup a little so
		# that things will work.  Install dosemu2 and dos2unix here,
		# since we need them now.
		#
	sudo apt-get update -y
	sudo apt-get install -y dosemu2 dos2unix
	dpkg -L dosemu2
	rm -rf ~/.dosemu
	rm -f dosemu/freedos/config.sys
	echo lastdrive=z >dosemu/freedos/config.sys
	dos2unix <dosemu/freedos/autoexec.bat | \
	    sed -e 's,z:\\dosemu,c:\\bin;c:\\dosemu;d:\\dosemu,g' \
		-e 's,unix -,system -,g' >dosemu/freedos/autoexec.bat.new
	mv dosemu/freedos/autoexec.bat.new dosemu/freedos/autoexec.bat
	cat dosemu/freedos/autoexec.bat
		#
		# Prime the dosemu2 installation.  For some reason, dosemu.bin
		# may segfault the first time it tries to set up ~/.dosemu/ .
		#
	until (echo; echo exitemu) | \
	    dosemu.bin -I 'video {none} keyboard {layout us}' \
	    -i"`pwd`"/dosemu/freedos
		do true; done
		#
		# Do a quick test to see if dosemu2 works as expected.
		#
	dosemu.bin -I 'video {none} keyboard {layout us}' -p -K \
	    dosemu/freedos/bin/mem.exe;;
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
