#!/bin/bash

curdir=$(cd $(dirname $0); pwd)
cmd=../ltsview
counter=1
tests=4

echo "1..${tests}"

is () {
    ret=$1
    exp=$2

    if [[ "$ret" = "$exp" ]] ; then
	echo ok $counter
	counter=$(expr $counter +  1 )
    else
	echo not ok
	echo "$ret"
	echo "$exp"
    fi

}

diag () {
    echo $1 >&2
}
ret=$(printf 'l1:v1' | $cmd)
exp="=========
l1: v1"

is "$ret" "$exp"

ret=$(printf 'l1:v1\n' | $cmd)
exp="=========
l1: v1"

is "$ret" "$exp"

ret=$(printf 'l1:v1\tl2:v2\nl3:v3' | $cmd)
exp="=========
l1: v1
l2: v2
=========
l3: v3"

is "$ret" "$exp"

ret=$(printf 'l1:v1\tl2:v2\nl3:v3' | $cmd -k l1,l3)
exp="=========
l1: v1
=========
l3: v3"

is "$ret" "$exp"
