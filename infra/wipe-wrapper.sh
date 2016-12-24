#!/bin/sh

set -e
opts=
sep=
wheee=
while test -z "$wheee"; do
	case "$1" in
	    --)	wheee=+;;
	    -*)	opts="$opts $1"
		shift;;
	    *)	wheee=+;;
	esac
done
if test x-- = x"$1"
	then shift; fi
for f in ${1+"$@"}; do
	if test -e "$f"
		then wipe -f -q -s -Q1 $opts "$f"; fi
done
