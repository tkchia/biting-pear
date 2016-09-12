> "*A popular tourist attraction of the region, the biting pear lives off low-flying birds, hand-outs, and the occasional unwary sightseer.*" --&nbsp;[ursulav](http://ursulav.deviantart.com/art/The-Biting-Pear-of-Salamanca-29677500)

[![(build status)](https://travis-ci.org/tkchia/innocent-pear.svg?branch=master)](https://travis-ci.org/tkchia/innocent-pear)

## Synopsis

#### Installation

> `git clone --recursive https://github.com/tkchia/innocent-pear.git`

> ...*install* `g++` *or* `clang++`, *and* `libbfd`...

> [*source-path*`/`]`configure` [`--prefix=`*install-path*] [`--target=`*target-arch*] [`--target-dir=`*target-install-path*] [...]

> `make check`

> `make install`

#### Use

> [*install-path*`/bin/`]`innocent-pear-c++` [`-Xinnocent-pear -doge`] [...] [*g++-options*...]

## Description

`innocent-pear-c++` is a wrapper around the GNU C++ compiler (`g++`(1)) or `clang++` compiler which tries to obscure the code of compiled programs.

If `-Xinnocent-pear -doge` is specified, it scrambles parts of the text and data sections of a program and adds constructor routines to unscramble them.

There is also a rather undocumented C++ API for various code obfuscation subtasks.

## Bugs

**(1)** The scrambling of text and data is probably not yet very strong.

**(2)** The C++ API should really be documented.

**(3)** Compiling for an x86-32 target using `g++` 4.8.4 may cause the compiler to crash:

```
./share/innocent-pear/doge-01.cc: In function ‘void unscramble_01_1()’:
./share/innocent-pear/doge-01.cc:73:1: internal compiler error: Segmentation fault
 }
 ^
Please submit a full bug report,
with preprocessed source if appropriate.
See <file:///usr/share/doc/gcc-4.8/README.Bugs> for instructions.
```

I do not know what exactly is causing this.  For now, consider using either `g++` 5 or above, or `clang++`, to compile x86-32 code.

**(4)** If `innocent-pear` is explicitly set up to compile target-side programs

  * using `clang++`
  * with `libstdc++` linked in dynamically (i.e. no `-static` or `-static-libstdc++`)
  * where the programs handle exceptions,

the programs may fail with a runtime error on certain platforms, including x86-64 and x86-32:

```
./test/test-doge-eh.debug: error while loading shared libraries: unexpected reloc type 0x18
```

This is because I have not found a clean way to break up the absolute relocations referring to RTTI structures in `libstdc++` (`_ZTIi`, etc.), or to separate the relocations from the scrambled data.

Linux/ARM32 platforms (`arm*-linux-gnueabi` and `arm*-linux-gnueabihf`) should be free of this problem, since ARM exception tables are position independent.
