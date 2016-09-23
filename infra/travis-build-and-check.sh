#!/bin/sh

set -e -v
mkdir build-$$
cd build-$$
../configure --help
../configure ${TARGET:+"--target=$TARGET"}
make
exec make check
