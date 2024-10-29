#!/bin/bash
if [ $# -lt 1 ]; then
	echo "usage: batch_anlz <dbdir>"
	exit
fi
mkdir -p "out"
for dbfile in `ls $1`; do
	if [ -f "$1$dbfile" ]; then
		echo "./dbanlz -d $1$dbfile >out/$dbfile.out 2>>out/$dbfile"
		./dbanlz -d $1$dbfile >out/$dbfile.out 2>>out/$dbfile
	fi;
done
