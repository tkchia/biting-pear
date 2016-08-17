#!/bin/sh

set -e -v
./configure --help
./configure ${TARGET:+"--target=$TARGET"}
make
exec make check
